//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Adrián Matušík <xmatus35@stud.fit.vutbr.cz>
// $Date:       $2022-03-02
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Adrián Matušík
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
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int keys[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };

        for(int i = 0; i < 14; ++i)
            tree.InsertNode(keys[i]);
    }

    BinaryTree tree;
};

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int keys[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };

        for(int i = 0; i < 14; ++i)
            tree.InsertNode(keys[i]);
    }

    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode)
{
    EXPECT_TRUE(tree.GetRoot() == NULL);

    tree.InsertNode(0);
    ASSERT_TRUE(tree.GetRoot() != NULL);
    EXPECT_EQ(tree.GetRoot()->key, 0);

    tree.InsertNode(100);
    ASSERT_TRUE(tree.GetRoot() != NULL);
    EXPECT_EQ(tree.GetRoot()->key, 0);
}

TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(0));
}

TEST_F(EmptyTree, FindNode)
{
    EXPECT_TRUE(tree.FindNode(0) == NULL);
    EXPECT_TRUE(tree.FindNode(20) == NULL);
}

TEST_F(NonEmptyTree, InsertNode)
{
    tree.InsertNode(100);
    EXPECT_EQ(tree.GetRoot()->key, 30);

    tree.InsertNode(0);
    EXPECT_EQ(tree.GetRoot()->key, 30);
}

TEST_F(NonEmptyTree, DeleteNode_BCK)
{
    EXPECT_FALSE(tree.DeleteNode(0));
    EXPECT_TRUE(tree.DeleteNode(15));
    EXPECT_FALSE(tree.DeleteNode(15));


    int keys[] = { 5, 10, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };
    for(int i = 0; i < 13; ++i)
    {
        EXPECT_TRUE(tree.DeleteNode(keys[i]));
    }

    tree.DeleteNode(90);
    EXPECT_TRUE(tree.GetRoot() == NULL);
}

TEST_F(NonEmptyTree, DeleteNode_FWD)
{
    EXPECT_FALSE(tree.DeleteNode(0));

    int keys[] = { 90, 85, 80, 70, 65, 60, 55, 50, 40, 30, 20, 15, 10, 5 };
    for(int i = 0; i < 13; ++i)
    {
        EXPECT_TRUE(tree.DeleteNode(keys[i]));
    }

    tree.DeleteNode(5);
    EXPECT_TRUE(tree.GetRoot() == NULL);
}

TEST_F(NonEmptyTree, FindNode)
{
    int keys[] = { 5, 10, 15, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };
    for(int i = 0; i < 14; ++i)
    {
        BinaryTree::Node_t *pNode = tree.FindNode(keys[i]);
        ASSERT_TRUE(pNode != NULL);
        EXPECT_EQ(pNode->key, keys[i]);
    }

    EXPECT_TRUE(tree.FindNode(0) == NULL);
    EXPECT_FALSE(tree.FindNode(20) == NULL);
    EXPECT_TRUE(tree.FindNode(70) != NULL);
}

TEST_F(TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t *> outLeafNodes;
    tree.GetLeafNodes(outLeafNodes);
    for(BinaryTree::Node_t *lNode : outLeafNodes){
        ASSERT_EQ(lNode->color, BinaryTree::BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t *> outNonLeafNodes;
    tree.GetLeafNodes(outNonLeafNodes);
    for(BinaryTree::Node_t *lNode : outNonLeafNodes){
        if(lNode->color == BinaryTree::RED){
            ASSERT_EQ(lNode->pLeft->color, BinaryTree::BLACK);
            ASSERT_EQ(lNode->pRight->color, BinaryTree::BLACK);
        }
    } 
}

TEST_F(TreeAxioms, Axiom3)
{
    std::vector<BinaryTree::Node_t *> outLeafNodes;
    tree.GetLeafNodes(outLeafNodes);
    int bcount = 0, pcount = 0;
    int array[sizeof(outLeafNodes)];
    for(BinaryTree::Node_t *lNode : outLeafNodes){
        pcount++;
        while(lNode != tree.GetRoot()){
            if(lNode->color == BinaryTree::BLACK){
                bcount++;
            }
            lNode = lNode->pParent;
        }
        array[pcount-1] = bcount;
        bcount = 0;
    }
    for(int i = 0; i < pcount-1; i++){
        ASSERT_EQ(array[i], array[i+1]);
    }
}

/*** Konec souboru black_box_tests.cpp ***/
