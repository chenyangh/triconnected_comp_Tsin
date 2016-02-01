//
//  Tricomp.cpp
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//

#include "Tricomp.h"
#include <iostream>
#include <fstream>
using namespace std;
graph::graph(int number_of_vertices)
{
    vertex_info = new vertex*[number_of_vertices]; //
    for (int i = 0; i < number_of_vertices; i ++ )
    {
        vertex_info[i] = new vertex;
        vertex_info[i]->vertex_id = i;
    }
}

void graph::read_edges_from_file(string path_of_file)
{
    try {
        std::ifstream in_file(path_of_file);
        int first, second;
        while( in_file>>first>>second )
        {
            
            if(is_graph_start_from_zero){
                vertex * new_vertex = new vertex;
                new_vertex->vertex_id = second;
                new_vertex->next = vertex_info[first]->next;
                vertex_info[first]->next = new_vertex ; // Vertices indexed start from 1.
            }
            else{
                vertex * new_vertex = new vertex;
                new_vertex->vertex_id = second - 1;
                new_vertex->next = vertex_info[first - 1]->next;
                vertex_info[first - 1]->next = new_vertex ;
            }
        }
        
    } catch (...) {
        cerr << "Failed to open graph file!";
        exit(1);
    }
}

//=============================================
// Perform a first DFS to calcuate LOW1 LOW2 and adjust the adjacancy list
// to make the first child be the fist entry in the list
// refered to http://cobweb.cs.uga.edu/~rwr/STUDENTS/fsunms.pdf PAGE 21, and changed
// recursion to iteration
// --Chenyang 31st Jan
//=============================================
void graph::dfs_1()
{
    Stack<vertex *> * adjacent_list_pos_stack = new Stack<vertex *>();
    vertex* current_pos_adjacent_list;
    
    int current_vertex_id = 0; // choose the start vertex
    
    // visit the start vertex
    current_pos_adjacent_list = vertex_info[current_vertex_id];
    current_pos_adjacent_list->is_visited = true;
    adjacent_list_pos_stack->push(current_pos_adjacent_list);
    cout << current_pos_adjacent_list->vertex_id + 1 << endl;

    // Traverse the graph using iteration but not recursion
    while ( ! adjacent_list_pos_stack->is_empty() )
    {
        if ( current_pos_adjacent_list->next != nullptr)
        {
            if ( ! vertex_info[current_pos_adjacent_list->next->vertex_id]->is_visited )
            {

                current_pos_adjacent_list = vertex_info[current_pos_adjacent_list->next->vertex_id];
                current_pos_adjacent_list->is_visited = true;
                adjacent_list_pos_stack->push(current_pos_adjacent_list);
                
                // Visit the vertex( except for the start vertex)
                
                cout << current_pos_adjacent_list->vertex_id + 1<< endl;  // Here is where the vertex is visited
                
                
                
                
                
                
            }
            else // continue to next vertex of the adjacent list
            {
                current_pos_adjacent_list = current_pos_adjacent_list->next;
            }
        }
        else // Pop stack
        {
            current_pos_adjacent_list = adjacent_list_pos_stack->pop();
            // where the backstracks are ...
        }
        

        
    }
    
 
}



