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
{   cout << current_vertices_size << "====" <<endl;
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
    cout << current_vertices_size << "====" <<endl;
    cout << "low1, low2, dfs_number are:" << endl;
    for ( int i = 0 ; i < current_vertices_size ; i ++ )
    {
        cout << "vertex " << i << ": dfs_number = " << vertex_info[i].dfs_number <<  "; low 1 = " << vertex_info[i].low1 <<
        "; low 2 = " << vertex_info[i].low2 << "; father = " << vertex_info[i].father << endl;
    }
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
        for ( int i = 0 ; i < max_edges_size ; i ++ )
        {
            adjacency_list[i] =  new vertex;
            adjacency_list[i]->vertex_id = i;
        }
        while( in_file>>first>>second )
        {
            // NOTE: Follwing - 1 depends on the input file
            int from  = first - 1;
            int to = second - 1;
            
            current_vertices_size = ( from + 1) > current_vertices_size ? (from + 1) : current_vertices_size ;
           
            cout << current_vertices_size << endl;
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
            
            // updating edge and vertices size
            
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
// first implement the recursion virsion
//=============================================

void graph::dfs_1()
{
    // initial variabels
    vertex_info  = (vertex_info_struct * ) malloc( current_vertices_size * sizeof(vertex_info_struct) );
    if ( vertex_info == nullptr)
    {
        cerr << " NO ENOUGH MEMORY!";
        exit(1);
    }
    for ( int i = 0 ; i < current_vertices_size ; i ++ )
    {
        vertex_info[i].low1 = vertex_info[i].low2 = 0;
        vertex_info[i].dfs_number = vertex_info[i].father = 0;
    }
    time = 0;
    int root = 0;
    dfs_1_recur(root);
    
    // has to adjust the adjacency list
    
}

void graph::dfs_1_recur(int v)
{
    vertex_info[v].dfs_number = time = time + 1;
    vertex_info[v].low1 = vertex_info[v].low2 = vertex_info[v].dfs_number;
    vertex_info[v].nd = 1;
    if (adjacency_list[v]->next == nullptr)
        return;
    vertex * cur_ver = adjacency_list[v]->next;
    
    while (cur_ver != nullptr) // FOR w in the adjacency list of v DO
    {
        int w = cur_ver->vertex_id;
        if ( vertex_info[w].dfs_number == 0 )
        {
           // NOTE  mark vw as a tree edge in P; NOT DONE
            vertex_info[w].father = v;
            dfs_1_recur(w);
            if ( vertex_info[w].low1 < vertex_info[v].low1 )
            {
                vertex_info[v].low2 =  vertex_info[v].low1 < vertex_info[w].low2  ? vertex_info[v].low1 : vertex_info[w].low2; //LOWPT2(v) = MIN{LOWPT1(v), LOWPT2(w)};
                vertex_info[v].low1 = vertex_info[w].low1;
            }
            else if ( vertex_info[w].low1 == vertex_info[v].low1 )
                vertex_info[v].low2 = vertex_info[w].low1;
            else
                vertex_info[v].low2 = vertex_info[v].low2 < vertex_info[w].low1  ? vertex_info[v].low2 : vertex_info[w].low1; //LOWPT2(v) = MIN{LOWPT2(v), LOWPT1(w)};
            vertex_info[v].nd = vertex_info[v].nd + vertex_info[w].nd; // NOTE: may not needed.
        }
        else if ( vertex_info[w].dfs_number < vertex_info[v].dfs_number && w != vertex_info[v].father )
        {
            // NOTE mark vw as a frond in P; NOT DONE
            if ( vertex_info[w].dfs_number < vertex_info[v].low1 )
            {
                vertex_info[v].low2 = vertex_info[v].low1;
                vertex_info[v].low1 = vertex_info[w].dfs_number;
            }
            else if ( vertex_info[w].dfs_number == vertex_info[v].low1 )
                vertex_info[v].low2 = vertex_info[w].dfs_number;
            else
                vertex_info[v].low2 =  vertex_info[v].low2 < vertex_info[w].dfs_number ? vertex_info[v].low2 : vertex_info[w].dfs_number; //LOWPT2(v) = MIN{LOWPT2(v), NUMBER(w)};
        }
        
        cur_ver = cur_ver->next;
    }
    
    
}



