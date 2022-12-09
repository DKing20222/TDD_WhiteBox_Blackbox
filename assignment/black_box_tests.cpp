//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNodeNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class NonEmptyTree : public ::testing::Test {
protected:
    virtual void SetUp() {
        int values[] = {10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55};

        for (auto value: values)
            tree.InsertNode(value);
    }

    BinaryTree tree;
};

class EmptyTree : public ::testing::Test {
protected:
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test {
protected:
    BinaryTree tree;
};

TEST_F(NonEmptyTree, InsertNode) {
    EXPECT_TRUE(tree.InsertNode(1).first);

    EXPECT_FALSE(tree.InsertNode(5).first);
}

TEST_F(NonEmptyTree, DeleteNode) {
    EXPECT_TRUE(tree.DeleteNode(5));

    EXPECT_FALSE(tree.DeleteNode(1));
}

TEST_F(NonEmptyTree, FindNode) {
    EXPECT_TRUE(tree.FindNode(5) != NULL);

    EXPECT_TRUE(tree.FindNode(1) == NULL);
}

TEST_F(EmptyTree, InsertNode) {
    EXPECT_TRUE(tree.InsertNode(1).first);
    EXPECT_TRUE(tree.InsertNode(5).first);
}

TEST_F(EmptyTree, DeleteNode) {
    EXPECT_FALSE(tree.DeleteNode(5));
    EXPECT_FALSE(tree.DeleteNode(1));
}

TEST_F(EmptyTree, FindNode) {
    EXPECT_TRUE(tree.FindNode(5) == NULL);
    EXPECT_TRUE(tree.FindNode(1) == NULL);
}

/*** Konec souboru black_box_tests.cpp ***/
