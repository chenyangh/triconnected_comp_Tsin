//
//  main.cpp
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//

#include <iostream>
#include "Tricomp.h"
int main(int argc, const char * argv[]) {
    
    graph * graph_instance = new graph(13);
    graph_instance->read_edges_from_file("/Users/chenyanghuang/Desktop/499/compare/test.txt");
    // FIRST STEP, CHECK IF THE GRAPH IS SIMPLE GRAPH
    graph_instance->print_adjacency_list();
    
    // SECOND STEP, PERFORM THE FIRST DFS,,, ? NOT IMPLEMENTED
    //graph_instance->dfs_1();
    
    
    // THIRD STEP,
    
    
    
    return 0;
}
