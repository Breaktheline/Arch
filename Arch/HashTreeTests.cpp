#include "gtest/gtest.h"
#include "HashTree.h"

TEST(HashTreeTest, ShouldNotFindNewNode)
{
	HashTree hashTree;

	unsigned int hash = hashTree.GetHash(98, 970);
	int index = hashTree.FindNodeIndex(98, 970, hash);

	ASSERT_EQ(2038, hash);
	ASSERT_EQ(NIL, index);
}

TEST(HashTreeTest, ShouldAddNewNode)
{
	HashTree hashTree;

	unsigned int hash = hashTree.GetHash(98, 970);
	Node* node = hashTree.AddNode(98, 970, hash);

	ASSERT_TRUE(node != NULL);
	ASSERT_EQ(2038, hash);
	ASSERT_EQ(2038, node->index);
	ASSERT_EQ(98, node->symbol);
	ASSERT_EQ(970, node->parent);
}

TEST(HashTreeTest, ShouldFindExistingNode)
{
	HashTree hashTree;

	unsigned int hash = hashTree.GetHash(98, 970);
	Node* node = hashTree.AddNode(98, 970, hash);
	int index = hashTree.FindNodeIndex(98, 970, hash);

	ASSERT_NE(NIL, index);
	ASSERT_EQ(2038, index);
}

TEST(HashTreeTest, ShouldFindIfKeyIsGreaterThanTableSize)
{
	HashTree hashTree;

	unsigned int hash = hashTree.GetHash(255, 65535);
	Node* node = hashTree.AddNode(255, 65535, hash);
	int index = hashTree.FindNodeIndex(255, 65535, hash);

	ASSERT_EQ(32513, hash);
	ASSERT_TRUE(node != NULL);
	ASSERT_EQ(32513, node->index);
	ASSERT_EQ(255, node->symbol);
	ASSERT_EQ(65535, node->parent);
	ASSERT_EQ(32513, index);
}

TEST(HashTreeTest, ShouldFindIfCollisionHappened)
{
	HashTree hashTree;
	unsigned int hash1 = hashTree.GetHash(4, 25);
	unsigned int hash2 = 4;
	Node* node1 = hashTree.AddNode(4, 25, hash1);
	int index1 = hashTree.FindNodeIndex(4, 25, hash1);

	ASSERT_EQ(54, node1->index);
	ASSERT_EQ(25, node1->parent);
	ASSERT_EQ(4, node1->symbol);

	ASSERT_EQ(54, hash1);
	ASSERT_EQ(256, index1);
}

TEST(HashTreeTest, ShouldFindString)
{
	HashTree hashTree;

	unsigned int hash = hashTree.GetHash(107,103);
	Node* node1 = hashTree.AddNode(99, 56, hashTree.GetHash(99, 56));
	Node* node2 = hashTree.AddNode(103,99, hashTree.GetHash(103,99));
	Node* node3 = hashTree.AddNode(103,103, hashTree.GetHash(103,103));
	Node* node4 = hashTree.AddNode(107,103, hash);

	int index = hashTree.FindNodeIndex(107,103, hash);

	ASSERT_TRUE(node1 != NULL);
	ASSERT_TRUE(node2 != NULL);
	ASSERT_TRUE(node3 != NULL);
	ASSERT_TRUE(node4 != NULL);

	ASSERT_EQ(165, hash);
	ASSERT_EQ(259, index);
}


TEST(HashTreeTest, ShouldNotAddIfTableIsFull)
{
	HashTree hashTree;
	Node* node;
	for(int i = 0; i < 32768; i++)
	{
		node = hashTree.AddNode(99, i, hashTree.GetHash(99, i));
	}

	ASSERT_TRUE(node == NULL);
}

TEST(HashTreeTest, ShouldFindAllIfTableIsMoreThenCodes)
{
	HashTree hashTree;
	Node* node;
	for(int i = 0; i < 32512; i++)
	{
		node = hashTree.AddNode(99, i, hashTree.GetHash(99, i));
		ASSERT_TRUE(node != NULL);
	}
}