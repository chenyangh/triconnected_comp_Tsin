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
// code can be improved by given size of the graph
graph::graph(int number_of_vertices)
{
    
}
graph::~graph()
{
    
}

void graph::print_adjacency_list()
{
    cout << "The current adjacency list is(starting from one):" << endl;
    for ( int i = 0 ; i < current_vertices_size ; i ++)
    {
        vertex* current_vertex = adjacency_list[i];
        
        if ( current_vertex->next != nullptr)
        {
            cout << current_vertex->vertex_id + 1 << "->";
            while ( current_vertex->next != nullptr )
            {
                cout << current_vertex->next->vertex_id + 1 ;
                if (current_vertex->next->next != nullptr)
                    cout << "->" ;
                current_vertex = current_vertex->next;
            }
            cout << endl;
        }
    }
    cout << " =============END==============" << endl;
}



// =====================================================
// This function automaticall detected size of graph whith dynamically allocation of memory
// NOTE that the vertices ID start from 0
// Current stratage is double the maximum size when needed, this could be improved.
// =====================================================
void graph::read_edges_from_file(string path_of_file)
{
    try {
        std::ifstream in_file(path_of_file);
        int first, second;
        adjacency_list = ( vertex ** ) malloc( sizeof(vertex** ) * max_vertices_size );
        for ( int i = 0 ; i < max_vertices_size ; i ++ )
        {
            adjacency_list[i] =  new vertex;
            adjacency_list[i]->vertex_id = i;
        }
        while( in_file>>first>>second )
        {
            if ( current_vertices_size >= max_vertices_size ) // dealling with maximum vertex size
            {
                adjacency_list = (vertex ** ) realloc(adjacency_list, sizeof(vertex** ) * max_vertices_size * 2 );
                for ( int i = max_vertices_size ; i < max_vertices_size * 2 ; i ++ )
                {
                    adjacency_list[i] =  new vertex;
                    adjacency_list[i]->vertex_id = i;
                }
                max_vertices_size *= 2;
            }
            
            // NOTE: Follwing - 1 depends on the input file
            int from  = first - 1;
            int to = second - 1;
            vertex* new_vertex = new vertex;
            new_vertex->vertex_id = to;
            
            // appending new adges, insert after head node
            if (adjacency_list[from]->next != nullptr)
            {
                new_vertex->next = adjacency_list[from]->next;
                adjacency_list[from]->next = new_vertex;
            }
            else
            {
                adjacency_list[from]->next = new_vertex;
            }
            
            // increasing current vertices size
            current_vertices_size  ++ ;
        }
        
    } catch ( std::exception &exc ) {
        cerr << exc.what();
    }
}

//=============================================
// Perform a first DFS to calcuate LOW1 LOW2 and adjust the adjacancy list
// to make the first child be the fist entry in the list
// refered to http://cobweb.cs.uga.edu/~rwr/STUDENTS/fsunms.pdf PAGE 11, and changed
// recursion to iteration
// --Chenyang 31st Jan.
//=============================================
//
//void graph::dfs_1()
//{
//    Stack<vertex *> * adjacent_list_pos_stack = new Stack<vertex *>();
//    vertex* current_pos_adjacent_list;
//    
//    int current_vertex_id = 0; // choose the start vertex
//    
//    // visit the start vertex
//    current_pos_adjacent_list = vertex_info[current_vertex_id];
//    current_pos_adjacent_list->is_visited = true;
//    adjacent_list_pos_stack->push(current_pos_adjacent_list);
//    cout << current_pos_adjacent_list->vertex_id + 1 << endl;
//
//    // Traverse the graph using iteration but not recursion
//    while ( ! adjacent_list_pos_stack->is_empty() )
//    {
//        if ( current_pos_adjacent_list->next != nullptr)
//        {
//            if ( ! vertex_info[current_pos_adjacent_list->next->vertex_id]->is_visited )
//            {
//
//                current_pos_adjacent_list = vertex_info[current_pos_adjacent_list->next->vertex_id];
//                current_pos_adjacent_list->is_visited = true;
//                adjacent_list_pos_stack->push(current_pos_adjacent_list);
//                
//                // Visit the vertex( except for the start vertex)
//                
//                cout << current_pos_adjacent_list->vertex_id + 1<< endl;  // Here is where the vertex is visited
//                
//                
//                
//                
//                
//                
//            }
//            else // continue to next vertex of the adjacent list
//            {
//                current_pos_adjacent_list = current_pos_adjacent_list->next;
//            }
//        }
//        else // Pop stack
//        {
//            current_pos_adjacent_list = adjacent_list_pos_stack->pop();
//            // where the backstracks are ...
//        }
//        
//
//        
//    }
//    
// 
//}



