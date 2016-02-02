//
//  Tricomp.h
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//

#ifndef _99_brand_new_Tricomp_h
#define _99_brand_new_Tricomp_h


#include "Tools.h"
using namespace std;



class graph
{
public:
    ~graph();
    graph(int number_of_vertices);
    void read_edges_from_file(string path_of_file);
    
    void dfs_1();
    void dfs_1_recur(int);
    
    void print_adjacency_list();
    
    
private:
    
    //bool is_graph_start_from_zero = false;  // it depends on how your input file is.
    
    struct vertex // data structure for saving information of vertices
    {
        int vertex_id = -1;
        
        bool is_visited = false;
        vertex* in_frond_list = nullptr;
        //vertex* previous;
        vertex* next = nullptr; // i.e. the adjacency list of certain vertex.
    };
    
    struct vertex_info_struct
    {
        int dfs_number = -1;
        int low1 = -1;
        int low2 = -1;
        int low3 = -1;
        int father = -1;
        int nd;
       // bool is_tree_edge = false;
    };
    
    vertex** adjacency_list;
    vertex_info_struct* vertex_info;
    int max_edges_size = 2; // doulbe when needed. reallocate.
    int max_vertices_size = 2;
    int current_edges_size = 0; //
    int current_vertices_size = 0;
    int time; // used when performing DFS1
};



#endif
