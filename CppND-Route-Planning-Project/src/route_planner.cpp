#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {

    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;


    this->start_node = &(m_Model.FindClosestNode(start_x,start_y));
    //*end_node = m_Model.FindClosestNode(end_x,end_y);
    this->end_node = &m_Model.FindClosestNode(end_x,end_y);
}


float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    //RouteModel::Node
    float h = 0;
    h = node->distance(*(this->end_node));
    return h;
}


void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();

    for (RouteModel::Node * n_node : current_node->neighbors){
        n_node->parent = current_node;
        n_node->h_value = this->CalculateHValue(n_node);
        n_node->g_value = current_node->g_value + current_node->distance(*n_node);//neighbor g_value =?
        open_list.push_back(n_node);
        n_node->visited = true;
    }
    
}


bool Compare(const RouteModel::Node * n1,const RouteModel::Node * n2){
    float f1 = n1->g_value + n1->h_value;
    float f2 = n2->g_value + n2->h_value;
    return f1 > f2;
}
RouteModel::Node *RoutePlanner::NextNode() {
    sort(this->open_list.begin(),this->open_list.end(),Compare);
    RouteModel::Node * n = this->open_list.back();
    this->open_list.pop_back();
    return n; 
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    //std::cout << "Entramos en el ConstructorFinalPath  \n";
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    RouteModel::Node *parent;
    //int i = 0;

    while(current_node->x != start_node->x && current_node->y != start_node->y){
            //i++;
            parent = current_node->parent;
            
            //Add distance
            distance += current_node->distance(*parent);
            
            //Store Node in path
            path_found.insert(path_found.begin(),*current_node);
            //path_found.push_back(*current_node);
           
            //Move to parent node
            current_node = parent;
            
            //std::cout << "current_node.x =" << current_node->x << std::endl;
            //std::cout << "current_node.y =" << current_node->y << std::endl;
            //std::cout << "el bucle no se acaba nunca\n";
            //std::cout << std::endl;
        }
    //std::cout << "longitud de camino = " << i << std::endl;
    
    //Add the initial node

    path_found.insert(path_found.begin(),*current_node); 

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


//A* Search algorithm here.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    


    this->open_list.push_back(this->start_node);
    this->start_node->visited = true;


    while(open_list.size() > 0){
        
 

        //Get next node
        current_node = this->NextNode();


        if((current_node->x == this->end_node->x) && (current_node->y == this->end_node->y)){
        //if(current_node == this->end_node){
            this->m_Model.path = this->ConstructFinalPath(current_node);
            return;
        }
        this->AddNeighbors(current_node);   
    }
    std::cout << "no path found\n";
    return;
}