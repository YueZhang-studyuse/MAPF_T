#pragma once

#include "Instance.h"
#include "ConstraintTable.h"

class LLNode // low-level node
{
public:
	int location;
	int g_val;
	int h_val = 0;
	LLNode* parent;
	int timestep = 0;
	int num_of_conflicts = 0;
	bool in_openlist = false;
	bool wait_at_goal; // the action is to wait at the goal vertex or not. This is used for >length constraints
	// the following is used to compare nodes in the OPEN list

	//direction
	int cur_direction = 0;

	struct compare_node
	{
		// returns true if n1 > n2 (note -- this gives us *min*-heap).
		bool operator()(const LLNode* n1, const LLNode* n2) const
		{
			if (n1->g_val + n1->h_val == n2->g_val + n2->h_val)
			{
				if (n1->h_val == n2->h_val)
				{
					//tie breaking for avoding turning and turn back (when parent and current are in the same location, wait wins)
					// if(n1->parent != nullptr && n2->parent != nullptr)
					// {
					// 	if(n1->location == n1->parent->location && n2->location == n2->location)
					// 	{
					// 		if(n1->cur_direction != n1->parent->cur_direction && n2->cur_direction == n2->parent->cur_direction)
					// 		{
					// 			return true;
					// 		}
					// 		else if(n2->cur_direction != n2->parent->cur_direction && n1->cur_direction == n1->parent->cur_direction)
					// 		{
					// 			return false;
					// 		}
					// 	}
					// }
					return rand() % 2;
					//return 0;
				}
				return n1->h_val >= n2->h_val;
			}
			return n1->g_val + n1->h_val >= n2->g_val + n2->h_val;
		}
	};  // used by OPEN (heap) to compare nodes (top of the heap has min f-val, and then highest g-val)

	// the following is used to compare nodes in the FOCAL list
	struct secondary_compare_node
	{
		bool operator()(const LLNode* n1, const LLNode* n2) const // returns true if n1 > n2
		{
			if (n1->num_of_conflicts == n2->num_of_conflicts)
			{
				if (n1->g_val == n2->g_val)
				{
					// if(n1->parent != nullptr && n2->parent != nullptr)
					// {
					// 	//tie breaking for avoding turning and turn back (when parent and current are in the same location, wait wins)
					// 	if(n1->location == n1->parent->location && n2->location == n2->location)
					// 	{
					// 		if(n1->cur_direction != n1->parent->cur_direction && n2->cur_direction == n2->parent->cur_direction)
					// 		{
					// 			return true;
					// 		}
					// 		else if(n2->cur_direction != n2->parent->cur_direction && n1->cur_direction == n1->parent->cur_direction)
					// 		{
					// 			return false;
					// 		}
					// 	}
					// }
					return rand() % 2 == 0;
					//return 0;
				}
				return n1->g_val <= n2->g_val;  // break ties towards larger g_vals
			}
			return n1->num_of_conflicts >= n2->num_of_conflicts;  // n1 > n2 if it has more conflicts
		}
	};  // used by FOCAL (heap) to compare nodes (top of the heap has min number-of-conflicts)


	LLNode() : location(0), g_val(0), h_val(0), parent(nullptr), timestep(0), num_of_conflicts(0), in_openlist(false), wait_at_goal(false) {}

	LLNode(int location, int cur_direction, int g_val, int h_val, LLNode* parent, int timestep, int num_of_conflicts = 0, bool in_openlist = false) :
		location(location), cur_direction(cur_direction), g_val(g_val), h_val(h_val), parent(parent), timestep(timestep),
		num_of_conflicts(num_of_conflicts), in_openlist(in_openlist), wait_at_goal(false) {}

	inline double getFVal() const { return g_val + h_val; }
	void copy(const LLNode& other)
	{
		location = other.location;
		g_val = other.g_val;
		h_val = other.h_val;
		parent = other.parent;
		timestep = other.timestep;
		num_of_conflicts = other.num_of_conflicts;
		wait_at_goal = other.wait_at_goal;
	}
};


class SingleAgentSolver
{
public:
	uint64_t num_expanded = 0;
	uint64_t num_generated = 0;

	double runtime_build_CT = 0; // runtime of building constraint table
	double runtime_build_CAT = 0; // runtime of building conflict avoidance table

	int start_location;
	int goal_location;
	//direction
	int start_direction;
	int goal_direction;

	vector<int> my_heuristic;  // this is the precomputed heuristic for this agent
	int compute_heuristic(int from, int to) const  // compute admissible heuristic between two locations
	{
		return instance.getManhattanDistance(from, to);
		//max(get_DH_heuristic(from, to), instance.getManhattanDistance(from, to));
	}
	int compute_heuristic(int from,int from_direc, int to, int to_direct) const  // compute admissible heuristic between two locations
	{
		return max(get_DH_heuristic(from,from_direc, to,to_direct), instance.getManhattanDistance(from, to));
		//max(get_DH_heuristic(from, to), instance.getManhattanDistance(from, to));
	}
	const Instance& instance;

	virtual Path findPath(const CBSNode& node, const ConstraintTable& initial_constraints,
		const vector<Path*>& paths, int agent, int lower_bound) = 0;
	virtual int getTravelTime(int end, int direction, const ConstraintTable& constraint_table, int upper_bound) = 0;
	virtual string getName() const = 0;
	virtual bool checkReachable(int end, const ConstraintTable& constraint_table, int timestep) = 0;

	list<int> getNextLocations(int curr) const; // including itself and its neighbors
	list<int> getNeighbors(int curr) const { return instance.getNeighbors(curr); }
	list<pair<int,int>> getNeighbors(int curr_loc, int curr_direction) const { return instance.getNeighbors(curr_loc,curr_direction);}

	// int getStartLocation() const {return instance.start_locations[agent]; }
	// int getGoalLocation() const {return instance.goal_locations[agent]; }

	SingleAgentSolver(const Instance& instance, int agent) :
		instance(instance), //agent(agent), 
		start_location(instance.start_locations[agent]),
		goal_location(instance.goal_locations[agent]),
		start_direction(instance.start_directions[agent]),
		goal_direction(instance.goal_directions[agent])
	{
		compute_heuristics();
	}

	//temp method to getting columns
	int getInstanceCols() const{
		int cols = instance.getCols();
		return cols;
	}
	bool validMove(int location1, int location2) const{
		return instance.validMove(location1,location2);
	}

	virtual ~SingleAgentSolver() {}

protected:
	void compute_heuristics();
	int get_DH_heuristic(int from, int to) const { return abs(my_heuristic[from] - my_heuristic[to]); }
	int get_DH_heuristic(int from, int from_direct, int to, int to_direct) const { return abs(my_heuristic[from*4+from_direct] - my_heuristic[to*4+to_direct]); }
};

