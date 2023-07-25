#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 10

// Function to calculate the distance between two cities
int calculateDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to find the shortest tour length using brute force
int tspBruteForce(int graph[MAX_CITIES][MAX_CITIES], int numCities) {
    int visited[MAX_CITIES] = {0};
    int minTour = INT_MAX;

    // Start from the first city (0)
    visited[0] = 1;

    // Try all possible permutations of cities
    int currentCity = 0;
    int countVisited = 1;
    int totalDistance = 0;

    for (int i = 0; i < numCities; i++) {
        if (visited[i]) {
            continue;
        }

        visited[i] = 1;
        countVisited++;
        totalDistance += graph[currentCity][i];

        // Recursive call to find the shortest tour starting from the current city
        minTour = min(minTour, totalDistance + tspBruteForce(graph, numCities));

        // Backtrack
        visited[i] = 0;
        countVisited--;
        totalDistance -= graph[currentCity][i];
    }

    // Return to the starting city
    if (countVisited == numCities) {
        return totalDistance + graph[currentCity][0];
    }

    return minTour;
}

int main() {
    int numCities;
    printf("Enter the number of cities (2 to %d): ", MAX_CITIES);
    scanf("%d", &numCities);

    if (numCities < 2 || numCities > MAX_CITIES) {
        printf("Invalid number of cities.\n");
        return 1;
    }

    int graph[MAX_CITIES][MAX_CITIES] = {0};

    printf("Enter the coordinates of each city (format: x y):\n");
    for (int i = 0; i < numCities; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        // Calculate distances between cities
        for (int j = 0; j < numCities; j++) {
            graph[i][j] = calculateDistance(x, y, graph[j][0], graph[j][1]);
        }
    }

    // Start the TSP from city 0
    int shortestTour = tspBruteForce(graph, numCities);

    printf("Shortest tour length: %d\n", shortestTour);

    return 0;
}
