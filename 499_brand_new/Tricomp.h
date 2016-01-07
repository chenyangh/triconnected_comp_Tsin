//
//  Tricomp.h
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//
#include "Tools.h"
#include <string>
#include <iostream>// for test
#ifndef _99_brand_new_Tricomp_h
#define _99_brand_new_Tricomp_h
using namespace std;



class graph
{
public:
    
    graph(int number_of_vertices);
    void read_edges_from_file(string path_of_file);
    void dfs_1();
    
    
private:
    
    bool is_graph_start_from_zero = false;  // it depends on how your input file is.
    
    struct vertex // data structure for saving information of vertices
    {
        int vertex_id = -1;
        int dfs_number = -1;
        int low1 = -1;
        int low2 = -1;
        int low3 = -1;
        bool is_visited = false;
        vertex* in_frond_list = nullptr;
        //vertex* previous;
        vertex* next = nullptr; // i.e. the adjacency list of certain vertex.
    };
    
    
    vertex** vertex_info;

};



#endif
