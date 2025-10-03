#include <iostream>
#include <fstream>
#include <string>
#include <climits>
//these additional libraries are added just for the beautification of code :)
#include<Windows.h>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;
void loadbar();
void polar();

void loadbar()
{
    system("COLOR 0e");


    char a = 177;
    cout << "\n\n\n\t\t\t\t\tOPTIMIZING ROUTE PLANNING...";
    cout << "\n\n\n\t\t\t";
    for (int i = 0;i < 55;i++)
    {
        cout << a;
    }
    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0;i < 40;i++)
    {
        cout << a;
        Sleep(150);
    }
    cout << endl;
    cout << endl;
    cout << endl;

}
void polar() {
    // Function to print a character with a specified delay
    auto printCharWithDelay = [](char ch, int delayMs) {
        this_thread::sleep_for(chrono::milliseconds(delayMs));
        cout << ch;
    };

    // Function to print text in yellow and bold
    auto printYellowBold = [](string text) {
        cout << "\033[1;33m" << text << "\033[0m"; // ANSI escape code for yellow color and bold
    };

    // Get the console window size
    int cols = 120; // Assuming a larger console width for better display

    // Characters for the surprise element
    char surpriseChars[] = "...";

    // Calculate center position for surprise element
    int surpriseCenter = (cols - strlen(surpriseChars)) / 2;

    // Print the surprise element with delay and centering
    for (char ch : surpriseChars) {
        printCharWithDelay(' ', 100); // Add leading spaces for centering
    }
    cout << setw(surpriseCenter) << ""; // Move cursor to center
    for (char ch : surpriseChars) {
        printCharWithDelay(ch, 200);
    }
    cout << endl;

    // Characters for the actual text with delays and spacing
    string bearText = " ~~ P  O  L  A  R - B  E  A  R ~~";

    // Calculate starting position for "POLAR BEAR" with extra space for aesthetics
    int bearStart = (cols - bearText.length() + 3) / 3;

    // Print "POLAR BEAR" with delays, left-alignment, and spacing
    cout << setw(bearStart) << ""; // Move cursor to the left
    for (char ch : bearText) {
        if (ch == ' ') {
            printCharWithDelay(' ', 100);
        }
        else {
            printYellowBold(string(1, ch)); // Print character in yellow and bold
            printCharWithDelay(' ', 50); // Add trailing spaces for aesthetics
        }
    }
    cout << endl;
}




struct Restaurant
{
 //initializing ordernames,locations and deliverytimelimmits as pointers because they are not known
    string name;
    int location;
    int numOrders;
    string* orderNames;
    int* orderLocations;
    int* deliveryTimeLimits;
};

void dijkstra(int** grid, int gridsize, int starting_vertex, int* dist) 
//dijsktra's starting brackets
{

    //this is an boolean array to keep track of whether specific vertex is explored or not
    bool* sptSet = new bool[gridsize * gridsize];//its size will be equal to no of vertices

    for (int i = 0; i < gridsize * gridsize; ++i) 
    {
        //at first defining all distances from vertex as infinity
        dist[i] = INT_MAX;
        //till now all are unexplored
        sptSet[i] = false;
    }
    //setting it to zero as the distance of vertex with itself is zero
    dist[starting_vertex] = 0;

    for (int count = 0; count < gridsize * gridsize - 1; count++) 
    {
        //u is at first initialized to -1
        int u = -1;
        for (int v = 0; v < gridsize * gridsize; v++) 
        {
            if (!sptSet[v] && (u == -1 || dist[v] < dist[u])) 
            {
                u = v;
            }
        }

        sptSet[u] = true;
        //!sptSet[u + gridsize] means still not explored
        //u represets vertices
        //grid[row - 1][col] != -1 it will make sure that the graph is connected
        //it will give us row and column number of vertex we are working on as row and col
        int row = u / gridsize;
        int col = u % gridsize;
        //the current shortest distance from the source vertex to the upper neighbor of u is dist[u - gridsize]
        if (row > 0 && grid[row - 1][col] != -1 && !sptSet[u - gridsize] && dist[u] + 1 < dist[u - gridsize]) {
            dist[u - gridsize] = dist[u] + 1;
        }
        //the current shortest distance from the source vertex to the below neighbor of u is dist[u + gridsize]
        if (row < gridsize - 1 && grid[row + 1][col] != -1 && !sptSet[u + gridsize] && dist[u] + 1 < dist[u + gridsize]) {
            dist[u + gridsize] = dist[u] + 1;
        }
        //the current shortest distance from the source vertex to the left neighbor of u is dist[u - 1]
        if (col > 0 && grid[row][col - 1] != -1 && !sptSet[u - 1] && dist[u] + 1 < dist[u - 1]) {
            dist[u - 1] = dist[u] + 1;
        }
        //the current shortest distance from the source vertex to the right neighbor of u is dist[u + 1]
        if (col < gridsize - 1 && grid[row][col + 1] != -1 && !sptSet[u + 1] && dist[u] + 1 < dist[u + 1]) {
            dist[u + 1] = dist[u] + 1;
        }
    }

    delete[] sptSet;
}//dijsktra's ending brackets

int findNearestOrder(int** grid, int gridsize, int riderLocation, int numOrders, int* orderLocations, bool* visited) {
    int nearestOrder = -1;
    int minDistance = INT_MAX;

    for (int i = 0; i < numOrders; i++) {
        if (!visited[i]) {
            int* dist = new int[gridsize * gridsize];
            dijkstra(grid, gridsize, riderLocation, dist);

            if (dist[orderLocations[i]] < minDistance) {
                minDistance = dist[orderLocations[i]];
                nearestOrder = i;
            }

            delete[] dist;
        }
    }

    return nearestOrder;
}

int main()
{
    cout << endl<<endl;
    polar();
    loadbar();
    //reading the input file
    ifstream infile("polarbearinput.txt");
    if (!infile)
    {
        //if error opening the file
        cerr << "Error opening input file\n";
        return 1;
    }

    int numTestCases;
    //first line of input file
    infile >> numTestCases;
    //it will run for as many test cases specified in the input file
    for (int testcase = 1; testcase <= numTestCases; testcase++)
    {
        int gridsize, n_riders, n_resturants;
        //second line of input file contains gridsize,no of riders and resturants
        infile >> gridsize >> n_riders >> n_resturants;

        int** grid = new int* [gridsize];
        for (int i = 0; i < gridsize; ++i)
        {
            grid[i] = new int[gridsize];
            for (int j = 0; j < gridsize; ++j)
            {
                //initializing all vertices to zero which also tells the graph is connected
                grid[i][j] = 0;
            }
        }
        //as many resturants creating dynamic location
        Restaurant* restaurants = new Restaurant[n_resturants];
        for (int r = 0; r < n_resturants; ++r)
        {
            //reading name,location and no orders of every resturant 
            infile >> restaurants[r].name >> restaurants[r].location >> restaurants[r].numOrders;
            restaurants[r].orderNames = new string[restaurants[r].numOrders];
            restaurants[r].deliveryTimeLimits = new int[restaurants[r].numOrders];
            restaurants[r].orderLocations = new int[restaurants[r].numOrders];

            for (int a = 0; a < restaurants[r].numOrders; ++a)
            {
                //reading every ordername,location and timelimit of every order
                infile >> restaurants[r].orderNames[a] >> restaurants[r].orderLocations[a] >> restaurants[r].deliveryTimeLimits[a];
            }
            //marking the index of visited resturant in the grid as visited (-1)
            grid[restaurants[r].location / gridsize][restaurants[r].location % gridsize] = -1;
        }

        int totalDeliveryTime = 0;
        //looping for all resturants
        for (int r = 0; r < n_resturants; ++r)
        {
            //starting location of rider is resturant
            int riderLocation = restaurants[r].location;
            bool* visited = new bool[restaurants[r].numOrders];
            for (int a = 0; a < restaurants[r].numOrders; ++a)
            {
                visited[a] = false;
            }
            //looping for all orders of specific resturant
            for (int a = 0; a < restaurants[r].numOrders; ++a)
            {
                //finding nearest order to rider
                int nearestOrder = findNearestOrder(grid, gridsize, riderLocation, restaurants[r].numOrders, restaurants[r].orderLocations, visited);
                //if not visited
                if (nearestOrder != -1)
                {
                    int orderLocation = restaurants[r].orderLocations[nearestOrder];
                    int deliveryTimeLimit = restaurants[r].deliveryTimeLimits[nearestOrder];

                    int* dist = new int[gridsize * gridsize];
                    //calculating shortest paths again for updated location
                    dijkstra(grid, gridsize, riderLocation, dist);
                    //so that order can be delivered within given time limit
                    if (dist[orderLocation] <= deliveryTimeLimit)
                    {
                        totalDeliveryTime += dist[orderLocation];
                        
                        cout << "                                Minimum time for Order " << restaurants[r].orderNames[nearestOrder] << ":" << dist[orderLocation]<<" unit" << endl;
                        visited[nearestOrder] = true;
                        // Update rider's location after delivering the order
                        riderLocation = orderLocation; 
                        // Update grid to mark the location as visited
                        grid[riderLocation / gridsize][riderLocation % gridsize] = -1; 
                    }
                    else
                    {
                        cout << "Order " << restaurants[r].orderNames[nearestOrder] << " cannot be delivered in time. Time taken: " << dist[orderLocation] << ", Time limit: " << deliveryTimeLimit << endl;
                    }

                    delete[] dist;
                }
            }

            delete[] visited;
        }
        //outputting result
        cout << "                                Total time for case " << testcase << ": " << totalDeliveryTime << " units" << endl<<endl;

        for (int i = 0; i < gridsize; ++i) {
            delete[] grid[i];
        }
        delete[] grid;

        for (int r = 0; r < n_resturants; ++r) {
            delete[] restaurants[r].orderNames;
            delete[] restaurants[r].deliveryTimeLimits;
        }
        delete[] restaurants;
    }
    

    infile.close();
    
   


    return 0;
    
}
