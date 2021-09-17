root = initial_node;
Goal = final_node;

function IDA*(){                                                                //Driver function
    threshold=heuristic(Start);
    while(1){                                                                   //run for infinity
        integer temp=search(Start,0,threshold);                                 //function search(node,g score,threshold)
        if(temp==FOUND)                                                         //if goal found
            return FOUND;                                             
        if(temp== ∞)                                                            //Threshold larger than maximum possible f value
            return;                                                             //or set Time limit exceeded
        threshold=temp;
    }
}

function Search(node, g, threshold){                                            //recursive function
    f=g+heuristic(node);
    if(f>threshold)                                                             //greater f encountered
        return f;
    if(node==Goal)                                                              //Goal node found
        return FOUND;
    integer min=MAX_INT;                                                        //min= Minimum integer
    foreach(tempnode in nextnodes(node)){
        //recursive call with next node as current node for depth search
        integer temp=search(tempnode,g+cost(node,tempnode),threshold);  
        if(temp==FOUND)                                                         //if goal found
            return FOUND;
        if(temp<min)                                                            //find the minimum of all ‘f’ greater than threshold encountered
            min=temp;
        }
        return min;                                                             //return the minimum ‘f’ encountered greater than threshold
    }

function nextnodes(node){
    return list of all possible next nodes from node;
}