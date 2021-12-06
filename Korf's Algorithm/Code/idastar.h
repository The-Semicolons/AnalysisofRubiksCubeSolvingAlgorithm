// idastar.h : This file contains the 'IDAStar' class.
// File Created by : Utkarsh Gupta [29.09.2021 13:28:05]
// 

#pragma once

// Local header files
#include "cube.h"


#include<Windows.h>

// Number of unique corner combinations.
#define CORNER_DATABASE_SIZE 88179840
// Number of half unique edge combinations.
#define EDGE_DATABASE_SIZE 42577920

#define positive_modulo(x, mod) (((x % mod) + mod) % mod)

#define U_FACE 0
#define L_FACE 1
#define F_FACE 2
#define R_FACE 3
#define B_FACE 4
#define D_FACE 5
#define NO_FACE 6

#define CLOCKWISE_TURN 1
#define DOUBLE_TURN 2
#define COUNTER_TURN 3

/// <summary>
/// 
/// </summary>
typedef struct movenode_t {
    uint8_t face;
    int turn_type;
    struct movenode_t* next_node;
} movenode_t;

    // mapping of each face to the face on the opposite side of the cube
    uint8_t opposite_faces[7] = { D_FACE, R_FACE, B_FACE, L_FACE, F_FACE, U_FACE, NO_FACE };

    /// <summary>
    /// Table for storing the pattern database of corner cubies.
    /// </summary>
    uint8_t cornerPatternDatabase[CORNER_DATABASE_SIZE];

    /// <summary>
    /// Table for storing the pattern database of edge cubies.
    /// Edge pattern databse is stored in two parts to reduce
    /// the space complexity of the algorithm.
    /// </summary>
    uint8_t edgePatternDatabase[2][EDGE_DATABASE_SIZE];

    /// <summary>
        /// Structure to store cube corners.
        /// </summary>
    typedef struct {
        uint8_t cid;
        uint8_t rotation;
    } corner;

    /// <summary>
    /// Structure to store cube corner sequence.
    /// </summary>
    typedef struct {
        corner corners[8];
    } cornerPattern;

    /// <summary>
    /// Structure to store cube edges.
    /// </summary>
    typedef struct {
        uint8_t eid;
        uint8_t flip;
    } edge;

    /// <summary>
    /// Structure to store cube edge sequence.
    /// </summary>
    typedef struct {
        edge edges[12];
    } edgePattern;

    /// <summary>
    /// Structure of a node to represent corner queue node.
    /// </summary>
    typedef struct cornerQueueNode {
        cornerPattern cs;
        uint8_t distance;
        struct cornerQueueNode* next;
    } cornerQueueNode;

    /// <summary>
    /// Structure of a node to represent edge queue node.
    /// </summary>
    typedef struct edgeQueueNode {
        edgePattern es;
        uint8_t distance;
        struct edgeQueueNode* next;
    } edgeQueueNode;

    /// <summary>
    /// 
    /// </summary>
    typedef struct {
        cornerPattern cornersystem;
        edgePattern edgesystem;
    } cube_t;

    /// <summary>
    /// 
    /// </summary>
    const cube_t solvedCube = { { {
        {0, 0}, { 1, 0 }, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}
    } }, { {
        {0,0},{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}
    } } };

    /// <summary>
    /// 
    /// </summary>
    cube_t cube = solvedCube;

    /// <summary>
    /// 
    /// </summary>
    const cornerPattern solvedCornerSequence = { {
        {0, 0}, { 1, 0 }, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}
    } };

    /// <summary>
    /// 
    /// </summary>
    const edgePattern solvedEdgeSequence = { {
        {0,0},{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}
    } };

    /// <summary>
    /// 
    /// </summary>
    const corner faceCorners[6][4] = {
        {
            {2, 0},
            {3, 0},
            {0, 0},
            {1, 0}
        },
        {
            {2, 1},
            {1, 2},
            {5, 1},
            {6, 2}
        },
        {
            {1, 1},
            {0, 2},
            {4, 1},
            {5, 2}
        },
        {
            {0, 1},
            {3, 2},
            {7, 1},
            {4, 2}
        },
        {
            {3, 1},
            {2, 2},
            {6, 1},
            {7, 2}
        },
        {
            {5, 0},
            {4, 0},
            {7, 0},
            {6, 0}
        }
    };

    /// <summary>
    /// 
    /// </summary>
    const uint8_t cornerFacelets[8][3] = {
        {U_FACE, R_FACE, F_FACE},
        {U_FACE, F_FACE, L_FACE},
        {U_FACE, L_FACE, B_FACE},
        {U_FACE, B_FACE, R_FACE},
        {D_FACE, F_FACE, R_FACE},
        {D_FACE, L_FACE, F_FACE},
        {D_FACE, B_FACE, L_FACE},
        {D_FACE, R_FACE, B_FACE}
    };

    /// <summary>
    /// 
    /// </summary>
    const edge faceEdges[6][4] = {
        {
            {2, 0},
            {3, 0},
            {0, 0},
            {1, 0}
        },
        {
            {1, 1},
            {5, 1},
            {9, 1},
            {6, 1}
        },
        {
            {0, 1},
            {4, 0},
            {8, 1},
            {5, 0}
        },
        {
            {3, 1},
            {7, 1},
            {11, 1},
            {4, 1}
        },
        {
            {2, 1},
            {6, 0},
            {10, 1},
            {7, 0}
        },
        {
            {8, 0},
            {11, 0},
            {10, 0},
            {9, 0}
        }
    };

    /// <summary>
    /// 
    /// </summary>
    const uint8_t edgeFacelets[12][2] = {
        {U_FACE, F_FACE},
        {U_FACE, L_FACE},
        {U_FACE, B_FACE},
        {U_FACE, R_FACE},
        {F_FACE, R_FACE},
        {F_FACE, L_FACE},
        {B_FACE, L_FACE},
        {B_FACE, R_FACE},
        {D_FACE, F_FACE},
        {D_FACE, L_FACE},
        {D_FACE, B_FACE},
        {D_FACE, R_FACE}
    };

    /// <summary>
    /// Storing the factirals of number from 0 to 11.
    /// </summary>
    int factorial[12] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800 };

    

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cs"></param>
    /// <param name="face"></param>
    /// <param name="i"></param>
    /// <returns></returns>
    uint8_t getFaceletCornerSystem(const cornerPattern* cs, uint8_t face, int i) {
        // find the corner orientation
        const corner* face_corner = &faceCorners[face][i];
        // find the physical corner at the orientation
        const corner* cornerx = &cs->corners[face_corner->cid];
        // find the inverse rotation of the physical corner
        uint8_t facelet_rotation = positive_modulo(face_corner->rotation - cornerx->rotation, 3);
        // return the facelet at the found rotation
        return cornerFacelets[cornerx->cid][facelet_rotation];
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="es"></param>
    /// <param name="face"></param>
    /// <param name="i"></param>
    /// <returns></returns>
    uint8_t getFaceletEdgeSystem(const edgePattern* es, uint8_t face, int i) {
        // find the edge orientation
        const edge* face_edge = &faceEdges[face][i];
        // find the physical edge at the orientation
        const edge* edgex = &es->edges[face_edge->eid];
        // find the inverse flip of the physical edge
        uint8_t facelet_flip = positive_modulo(face_edge->flip - edgex->flip, 2);
        // return the facelet at the found flip
        return edgeFacelets[edgex->eid][facelet_flip];
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cube"></param>
    /// <param name="face"></param>
    /// <param name="i"></param>
    /// <returns></returns>
    uint8_t getFaceletCube(const cube_t* cube, uint8_t face, uint8_t i) {
        // even indices are for corners, odd indices are for edges
        if (i % 2 == 0) {
            return getFaceletCornerSystem(&cube->cornersystem, face, i / 2);
        }
        else {
            return getFaceletEdgeSystem(&cube->edgesystem, face, (i - 1) / 2);
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cs"></param>
    /// <returns></returns>
    bool isSolvedCornerSystem(const cornerPattern* cs) {
        // corner ids should be in ascending order, corners should not be rotated
        for (int i = 0; i < 8; i++) {
            if (cs->corners[i].cid != i || cs->corners[i].rotation != 0) {
                return false;
            }
        }
        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="es"></param>
    /// <returns></returns>
    bool isSolvedEdgeSystem(const edgePattern* es) {
        // edge ids should be in ascending order, edges should not be flipped
        for (int i = 0; i < 12; i++) {
            if (es->edges[i].eid != i || es->edges[i].flip != 0) {
                return false;
            }
        }
        return true;
    }

    /// <summary>
    /// Calculating n Combination r or n Choose r for given
    /// n and r.
    /// </summary>
    /// <param name="n">Choose from</param>
    /// <param name="r">to be chosen</param>
    /// <returns></returns>
    int nCr(int n, int r) {
        return factorial[n] / (factorial[r] * factorial[n - r]);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cs"></param>
    /// <returns></returns>
    int encodeCornerSequence(const cornerPattern* cs) {
        int key = 0;
        for (int i = 0; i < 7; i++) {
            int numLess = 0;
            for (int j = i + 1; j < 8; j++) {
                if (cs->corners[i].cid > cs->corners[j].cid) {
                    numLess++;
                }
            }
            key += numLess * factorial[7 - i];
        }
        for (int i = 0; i < 7; i++) {
            key *= 3;
            key += cs->corners[i].rotation;
        }
        return key;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="es"></param>
    /// <param name="num"></param>
    /// <returns></returns>
    int encodeEdgeSequence(const edgePattern* es, int num) {
        if (num == 0) {
            int key = 0;
            int comb[6];
            int combI = 0;
            for (int i = 0; i < 12; i++) {
                if (es->edges[i].eid < 6) {
                    comb[combI] = i + 1;
                    combI++;
                }
            }
            int j = 0;
            for (int i = 0; i < 6; i++) {
                for (j++; j < comb[i]; j++) {
                    key += nCr(12 - j, 6 - i - 1);
                }
            }
            key *= 720;
            int perm[6];
            int permI = 0;
            for (int i = 0; i < 12; i++) {
                if (es->edges[i].eid < 6) {
                    perm[permI] = es->edges[i].eid;
                    permI++;
                }
            }
            for (int i = 0; i < 5; i++) {
                int numLess = 0;
                for (int j = i + 1; j < 6; j++) {
                    if (perm[i] > perm[j]) {
                        numLess++;
                    }
                }
                key += numLess * factorial[5 - i];
            }
            for (int i = 0; i < 12; i++) {
                if (es->edges[i].eid < 6) {
                    key *= 2;
                    key += es->edges[i].flip;
                }
            }
            return key;
        }
        else {
            int key = 0;
            int j = 0;
            int k = 0;
            for (int i = 0; i < 12; i++) {
                if (es->edges[i].eid >= 6) {
                    for (k++; k < i + 1; k++) {
                        key += nCr(12 - k, 6 - j - 1);
                    }
                    j++;
                }
            }
            key *= 720;
            int perm[6];
            int permI = 0;
            for (int i = 0; i < 12; i++) {
                if (es->edges[i].eid >= 6) {
                    perm[permI] = es->edges[i].eid - 6;
                    permI++;
                }
            }
            for (int i = 0; i < 5; i++) {
                int numLess = 0;
                for (int j = i + 1; j < 6; j++) {
                    if (perm[i] > perm[j]) {
                        numLess++;
                    }
                }
                key += numLess * factorial[5 - i];
            }
            for (int i = 0; i < 12; i++) {
                if (es->edges[i].eid >= 6) {
                    key *= 2;
                    key += es->edges[i].flip;
                }
            }
            return key;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="destination"></param>
    /// <param name="source"></param>
    /// <param name="face"></param>
    /// <param name="turn_type"></param>
    void turnCornerSequence(cornerPattern* destination, const cornerPattern* source, uint8_t face, int turn_type) {
        *destination = *source;
        // for each corner in the rotated face
        for (int i = 0; i < 4; i++) {
            // index of new corner position
            int j = (i + turn_type) % 4;
            // start corner orientation
            const corner* start_face_corner = &faceCorners[face][i];
            // end corner orientation
            const corner* end_face_corner = &faceCorners[face][j];
            // physical corner being moved between orientations
            const corner* cur_corner = &source->corners[start_face_corner->cid];
            // rotate by the difference between start and end orientation rotations
            uint8_t new_rotation = positive_modulo(cur_corner->rotation + end_face_corner->rotation - start_face_corner->rotation, 3);
            // set the corner id at the end orientation to the rotated corner's id
            destination->corners[end_face_corner->cid].cid = cur_corner->cid;
            // update the rotation for the rotated corner
            destination->corners[end_face_corner->cid].rotation = new_rotation;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="destination"></param>
    /// <param name="source"></param>
    /// <param name="face"></param>
    /// <param name="turn_type"></param>
    void turnEdgeSequence(edgePattern* destination, const edgePattern* source, uint8_t face, int turn_type) {
        *destination = *source;
        // for each edge in the rotated face
        for (int i = 0; i < 4; i++) {
            // index of new edge position
            int j = (i + turn_type) % 4;
            // start edge orientation
            const edge* start_face_edge = &faceEdges[face][i];
            // end edge orientation
            const edge* end_face_edge = &faceEdges[face][j];
            // physical edge being moved between orientations
            const edge* cur_edge = &source->edges[start_face_edge->eid];
            // flip the edge if the start and end edges are flipped differently
            uint8_t new_flip = positive_modulo(cur_edge->flip + end_face_edge->flip - start_face_edge->flip, 2);
            // set the edge id at the end orientation to the rotated edge's id
            destination->edges[end_face_edge->eid].eid = cur_edge->eid;
            // update the flip for the rotated edge
            destination->edges[end_face_edge->eid].flip = new_flip;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void generateCornerPatternDatabase() {
        for (int i = 0; i < CORNER_DATABASE_SIZE; i++) {
            cornerPatternDatabase[i] = 255;
        }
        cornerQueueNode* queue = (cornerQueueNode*)malloc(sizeof(cornerQueueNode));
        queue->cs = solvedCornerSequence;
        queue->distance = 0;
        queue->next = NULL;
        cornerQueueNode* queue_end = queue;
        cornerPatternDatabase[encodeCornerSequence(&(queue->cs))] = 0;
        int count = 0;
        while (queue != NULL) {
            count += 1;
            for (uint8_t face = 0; face < 6; face++) {
                for (int turn_type = 1; turn_type < 4; turn_type++) {
                    cornerPattern new_cs;
                    turnCornerSequence(&new_cs, &queue->cs, face, turn_type);
                    int code = encodeCornerSequence(&new_cs);
                    if (cornerPatternDatabase[code] == 255) {
                        cornerPatternDatabase[code] = queue->distance + 1;
                        cornerQueueNode* new_end = (cornerQueueNode*)malloc(sizeof(cornerQueueNode));
                        new_end->cs = new_cs;
                        new_end->distance = queue->distance + 1;
                        new_end->next = NULL;
                        queue_end->next = new_end;
                        queue_end = new_end;
                    }
                }
            }
            cornerQueueNode* nextQueue = queue->next;
            free(queue);
            queue = nextQueue;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="num"></param>
    void generateEdgePatternDatabase(int num) {
        if (num == 0) {
            for (int i = 0; i < EDGE_DATABASE_SIZE; i++) {
                edgePatternDatabase[0][i] = 255;
            }
            edgeQueueNode* queue = (edgeQueueNode*)malloc(sizeof(edgeQueueNode));
            queue->es = solvedEdgeSequence;
            queue->distance = 0;
            queue->next = NULL;
            edgeQueueNode* queue_end = queue;
            edgePatternDatabase[0][encodeEdgeSequence(&(queue->es), 0)] = 0;
            int count = 0;
            while (queue != NULL) {
                count += 1;
                for (uint8_t face = 0; face < 6; face++) {
                    for (int turn_type = 1; turn_type < 4; turn_type++) {
                        edgePattern new_es;
                        turnEdgeSequence(&new_es, &queue->es, face, turn_type);
                        int code = encodeEdgeSequence(&new_es, 0);
                        if (edgePatternDatabase[0][code] == 255) {
                            edgePatternDatabase[0][code] = queue->distance + 1;
                            edgeQueueNode* new_end = (edgeQueueNode*)malloc(sizeof(edgeQueueNode));
                            new_end->es = new_es;
                            new_end->distance = queue->distance + 1;
                            new_end->next = NULL;
                            queue_end->next = new_end;
                            queue_end = new_end;
                        }
                    }
                }
                edgeQueueNode* next_queue = queue->next;
                free(queue);
                queue = next_queue;
            }
        }
        else {
            for (int i = 0; i < EDGE_DATABASE_SIZE; i++) {
                edgePatternDatabase[1][i] = 255;
            }
            edgeQueueNode* queue = (edgeQueueNode*)malloc(sizeof(edgeQueueNode));
            queue->es = solvedEdgeSequence;
            queue->distance = 0;
            queue->next = NULL;
            edgeQueueNode* queue_end = queue;
            edgePatternDatabase[1][encodeEdgeSequence(&(queue->es), 1)] = 0;
            int count = 0;
            while (queue != NULL) {
                count += 1;
                for (uint8_t face = 0; face < 6; face++) {
                    for (int turn_type = 1; turn_type < 4; turn_type++) {
                        edgePattern new_es;
                        turnEdgeSequence(&new_es, &queue->es, face, turn_type);
                        int code = encodeEdgeSequence(&new_es, 1);
                        if (edgePatternDatabase[1][code] == 255) {
                            edgePatternDatabase[1][code] = queue->distance + 1;
                            edgeQueueNode* new_end = (edgeQueueNode*)malloc(sizeof(edgeQueueNode));
                            new_end->es = new_es;
                            new_end->distance = queue->distance + 1;
                            new_end->next = NULL;
                            queue_end->next = new_end;
                            queue_end = new_end;
                        }
                    }
                }
                edgeQueueNode* next_queue = queue->next;
                free(queue);
                queue = next_queue;
            }
        }
    }



    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    bool loadCornerPatternDatabase() {
        FILE* file = fopen("./corner.patterns", "rb");
        if (file == NULL)
            return false;
        size_t bytes_read = fread(cornerPatternDatabase, sizeof(uint8_t), CORNER_DATABASE_SIZE, file);
        fclose(file);
        if (bytes_read < CORNER_DATABASE_SIZE)
            return false;
        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="num"></param>
    /// <returns></returns>
    bool loadEdgePatternDatabase(int num) {
        if (num == 0) {
            FILE* file = fopen("./edge1.patterns", "rb");
            if (file == NULL)
                return false;
            size_t bytes_read = fread(edgePatternDatabase[0], sizeof(uint8_t), EDGE_DATABASE_SIZE, file);
            fclose(file);
            if (bytes_read < EDGE_DATABASE_SIZE)
                return false;
            return true;
        }
        else {
            FILE* file = fopen("./edge2.patterns", "rb");
            if (file == NULL)
                return false;
            size_t bytes_read = fread(edgePatternDatabase[1], sizeof(uint8_t), EDGE_DATABASE_SIZE, file);
            fclose(file);
            if (bytes_read < EDGE_DATABASE_SIZE)
                return false;
            return true;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    bool saveCornerPatternDatabase() {
        FILE* file = fopen("./corner.patterns", "wb");
        if (file == NULL)
            return false;
        size_t bytes_written = fwrite(cornerPatternDatabase, sizeof(uint8_t), CORNER_DATABASE_SIZE, file);
        fclose(file);
        if (bytes_written < CORNER_DATABASE_SIZE)
            return false;
        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="num"></param>
    /// <returns></returns>
    bool saveEdgePatternDatabase(int num) {
        if (num == 0) {
            FILE* file = fopen("./edge1.patterns", "wb");
            if (file == NULL)
                return false;
            size_t bytes_written = fwrite(edgePatternDatabase[0], sizeof(uint8_t), EDGE_DATABASE_SIZE, file);
            fclose(file);
            if (bytes_written < EDGE_DATABASE_SIZE)
                return false;
            return true;
        }
        else {
            FILE* file = fopen("./edge2.patterns", "wb");
            if (file == NULL)
                return false;
            size_t bytes_written = fwrite(edgePatternDatabase[1], sizeof(uint8_t), EDGE_DATABASE_SIZE, file);
            fclose(file);
            if (bytes_written < EDGE_DATABASE_SIZE)
                return false;
            return true;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void createPatternDatabase() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2);
        std::cout << std::endl << "Creating corner database.";
        generateCornerPatternDatabase();
        std::cout << std::endl << "Saving corner database.";
        saveCornerPatternDatabase();
        std::cout << std::endl << "Creating first edge database.";
        generateEdgePatternDatabase(0);
        std::cout << std::endl << "Saving first edge database.";
        saveEdgePatternDatabase(0);
        std::cout << std::endl << "Creating second edge database.";
        generateEdgePatternDatabase(1);
        std::cout << std::endl << "Saving second edge database.";
        saveEdgePatternDatabase(1);
        std::cout << std::endl << "Database created and saved successfully!!!" << std::endl << std::endl;
        SetConsoleTextAttribute(hConsole, 15);
    }

    /// <summary>
    /// Default constructor: Initialises and instance of class PatterDatabase.
    /// </summary>
    void loadDatabase() {
        if (loadCornerPatternDatabase() && loadEdgePatternDatabase(0) && loadEdgePatternDatabase(1)) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl << "Pattern database loaded successfully" << std::endl << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
        else {
            createPatternDatabase();
            loadCornerPatternDatabase();
            loadEdgePatternDatabase(0);
            loadEdgePatternDatabase(1);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << std::endl << "Pattern database loaded successfully" << std::endl << std::endl;
            SetConsoleTextAttribute(hConsole, 15);
        }
    }

    /// <summary>
    /// Returns the distence of current corner pieces from solved state.
    /// </summary>
    /// <param name="encodedCornerSequence">Current corner state.</param>
    /// <returns>Distance to solved state.</returns>
    uint8_t findCornerDistance(int encodedCornerSequence) {
        return cornerPatternDatabase[encodedCornerSequence];
    }

    /// <summary>
    /// Returns the distence of current edge pieces from solved state.
    /// </summary>
    /// <param name="num">Database number.</param>
    /// <param name="encodedEdgeSequence">Current edge state.</param>
    /// <returns>Distance to solved state.</returns>
    uint8_t findEdgeDistance(int encodedEdgeSequence, int num) {
        return edgePatternDatabase[num][encodedEdgeSequence];
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cube"></param>
    /// <returns></returns>
    bool isSolvedCube(const cube_t* cube) {
        return isSolvedCornerSystem(&cube->cornersystem) && isSolvedEdgeSystem(&cube->edgesystem);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="destination"></param>
    /// <param name="source"></param>
    /// <param name="face"></param>
    /// <param name="turn_type"></param>
    void turnCube(cube_t* destination, const cube_t* source, uint8_t face, int turn_type) {
        turnCornerSequence(&destination->cornersystem, &source->cornersystem, face, turn_type);
        turnEdgeSequence(&destination->edgesystem, &source->edgesystem, face, turn_type);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="cube"></param>
    /// <param name="face"></param>
    /// <param name="turn_type"></param>
    void turnCubeSelf(cube_t* cube,
        uint8_t face,
        int turn_type) {
        cube_t original_cube = *cube;
        turnCube(cube, &original_cube, face, turn_type);
    }

    bool prune_move(uint8_t face, uint8_t last_face) {
        if (face == last_face) {
            return true;
        }
        else if (face < 3 && face == opposite_faces[last_face]) {
            return true;
        }
        return false;
    }

    // checks each lookup table in succession, pruning if the depth is found to be invalid
    bool prune_state(const cube_t* cube, int depth) {
        int cornersystem_encoding = encodeCornerSequence(&cube->cornersystem);
        if (findCornerDistance(cornersystem_encoding) > depth) {
            return true;
        }
        int upper_edgesystem_encoding = encodeEdgeSequence(&cube->edgesystem, 0);
        if (findEdgeDistance(upper_edgesystem_encoding, 0) > depth) {
            return true;
        }
        int lower_edgesystem_encoding = encodeEdgeSequence(&cube->edgesystem, 1);
        if (findEdgeDistance(lower_edgesystem_encoding, 1) > depth) {
            return true;
        }
        return false;
    }

    // prepends a move to a chain of cube turns
    movenode_t* prependMoveNode(movenode_t* move_list, uint8_t face, int turn_type) {
        movenode_t* new_move_list = (movenode_t*) malloc(sizeof(movenode_t));
        new_move_list->face = face;
        new_move_list->turn_type = turn_type;
        new_move_list->next_node = move_list;
        return new_move_list;
    }

    movenode_t* searchDepth_rec(const cube_t* last_cube, int depth, uint8_t last_face) {
        cube_t cur_cube;
        // for each face and turn type combination
        for (uint8_t face = 0; face < 6; face++) {
            // remove unnecessary face turns
            if (prune_move(face, last_face)) continue;
            for (int turn_type = 1; turn_type < 4; turn_type++) {
                // perform the actual cube turn
                turnCube(&cur_cube, last_cube, face, turn_type);
                // if depth will be 0, check if the solution was found
                if (depth - 1 == 0) {
                    if (isSolvedCube(&cur_cube)) {
                        return prependMoveNode(NULL, face, turn_type);
                    }
                    // otherwise, if the state doesn't need to be pruned, search deeper
                }
                else if (!prune_state(&cur_cube, depth - 1)) {
                    
                    // save the solution so far, and simply prepend the recursive solution to it
                    movenode_t* partial_solution = searchDepth_rec(&cur_cube, depth - 1, face);
                    if (partial_solution != NULL) {
                        return prependMoveNode(partial_solution, face, turn_type);
                    }
                }
            }
        }
        return NULL;
    }

    /// <summary>
    /// This function performes a specific move on the cube.
    /// </summary>
    /// <param name="move">The move that needs to be performed. </param>
    void move(std::string move) {
        if (move == "F1") {
            turnCubeSelf(&cube, F_FACE, CLOCKWISE_TURN);
        }
        else if (move == "F2") {
            turnCubeSelf(&cube, F_FACE, DOUBLE_TURN);
        }
        else if (move == "F3") {
            turnCubeSelf(&cube, F_FACE, COUNTER_TURN);
        }
        else if (move == "U1") {
            turnCubeSelf(&cube, U_FACE, CLOCKWISE_TURN);
        }
        else if (move == "U2") {
            turnCubeSelf(&cube, U_FACE, DOUBLE_TURN);
        }
        else if (move == "U3") {
            turnCubeSelf(&cube, U_FACE, COUNTER_TURN);
        }
        else if (move == "B1") {
            turnCubeSelf(&cube, B_FACE, COUNTER_TURN);
        }
        else if (move == "B2") {
            turnCubeSelf(&cube, B_FACE, DOUBLE_TURN);
        }
        else if (move == "B3") {
            turnCubeSelf(&cube, B_FACE, CLOCKWISE_TURN);
        }
        else if (move == "R1") {
            turnCubeSelf(&cube, R_FACE, CLOCKWISE_TURN);
        }
        else if (move == "R2") {
            turnCubeSelf(&cube, R_FACE, DOUBLE_TURN);
        }
        else if (move == "R3") {
            turnCubeSelf(&cube, R_FACE, COUNTER_TURN);
        }
        else if (move == "L1") {
            turnCubeSelf(&cube, L_FACE, COUNTER_TURN);
        }
        else if (move == "L2") {
            turnCubeSelf(&cube, L_FACE, DOUBLE_TURN);
        }
        else if (move == "L3") {
            turnCubeSelf(&cube, L_FACE, CLOCKWISE_TURN);
        }
        else if (move == "D1") {
            turnCubeSelf(&cube, D_FACE, COUNTER_TURN);
        }
        else if (move == "D2") {
            turnCubeSelf(&cube, D_FACE, DOUBLE_TURN);
        }
        else if (move == "D3") {
            turnCubeSelf(&cube, D_FACE, CLOCKWISE_TURN);
        }
        else {
            std::cout << "ERROR" << std::endl;
        }
    }

    /// <summary>
    /// This function performes a set of moves on the cube.
    /// </summary>
    /// <param name="moves">List of moves needs to be performed on the cube.</param>
    void move(std::vector<std::string> moves) {
        for (int i = 0; i < moves.size(); i++) {
            move(moves[i]);
        }
    }

    /// <summary>
    ///  
    /// </summary>
    /// <param name="last_cube"></param>
    /// <param name="depth"></param>
    /// <param name="solution"></param>
    /// <param name="last_face"></param>
    /// <returns></returns>
    bool searchDepth(const cube_t* last_cube, int depth, movenode_t** solution, uint8_t last_face) {
        // if depth is 0, return empty solution if solved
        if (depth == 0) {
            if (isSolvedCube(last_cube)) {
                *solution = NULL;
                return true;
            }
            else {
                return false;
            }
            // otherwise, perform an actual recursive search
        }
        else {
            movenode_t* possible_solution = searchDepth_rec(last_cube, depth, last_face);
            if (possible_solution == NULL) {
                return false;
            }
            else {
                *solution = possible_solution;
                return true;
            }
        }
    }

    void findSolution() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        int cornerDistance = findCornerDistance(encodeCornerSequence(&cube.cornersystem));
        int edgeDistance1 = findEdgeDistance(encodeEdgeSequence(&cube.edgesystem, 0), 0);
        int edgeDistance2 = findEdgeDistance(encodeEdgeSequence(&cube.edgesystem, 1), 1);
        int depth = (std::max)(cornerDistance, (std::max)(edgeDistance1, edgeDistance2));

        movenode_t** solution = (movenode_t**) malloc(sizeof(movenode_t*));
        searchDepth(&cube, depth, solution, 0);
        
        movenode_t* solutionTemp = solution[0];
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "Steps to solve the cube: ";
        SetConsoleTextAttribute(hConsole, 2);
        while (solutionTemp->next_node != NULL) {
            if (solutionTemp->face == (uint8_t)0) {
                std::cout << "U";
            }
            if (solutionTemp->face == (uint8_t)1) {
                std::cout << "L";
            }
            if (solutionTemp->face == (uint8_t)2) {
                std::cout << "F";
            }
            if (solutionTemp->face == (uint8_t)3) {
                std::cout << "R";
            }
            if (solutionTemp->face == (uint8_t)4) {
                std::cout << "B";
            }
            if (solutionTemp->face == (uint8_t)5) {
                std::cout << "D";
            }
            std::cout << solutionTemp->turn_type << ", ";
            solutionTemp = solutionTemp->next_node;
        }
        std::cout << std::endl << std::endl;
    }