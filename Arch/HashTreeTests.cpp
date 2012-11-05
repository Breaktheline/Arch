#include "gtest/gtest.h"
#include "HashTree.h"

TEST(HashTreeTest, ShouldFindFirstSymbols)
{
	HashTree hashTree;

	Node* node1 = hashTree.GetNode('a');
	Node* node2 = hashTree.GetNode(255);

	ASSERT_FALSE(node1->IsEmpty());
	ASSERT_EQ(-1, node1->parent);
	ASSERT_EQ(97, node1->symbol);
	ASSERT_EQ(97, node1->index);

	ASSERT_FALSE(node2->IsEmpty());
	ASSERT_EQ(-1, node2->parent);
	ASSERT_EQ(255, node2->symbol);
	ASSERT_EQ(255, node2->index);
}

TEST(HashTreeTest, ShouldFindNewNode)
{
	HashTree hashTree;

	Node* node1 = hashTree.GetNode('b', 97);

	ASSERT_FALSE(node1->IsEmpty());
	ASSERT_EQ(97, node1->parent);
	ASSERT_EQ(98, node1->symbol);
	ASSERT_EQ(3138, node1->index);
}

TEST(HashTreeTest, ShouldFindExistingNode)
{
	HashTree hashTree;

	Node* node1 = hashTree.GetNode(98, 97);
	Node* node2 = hashTree.GetNode(98, 97);

	ASSERT_FALSE(node1->IsEmpty());
	ASSERT_FALSE(node2->IsEmpty());

	ASSERT_EQ(node1, node2);
	ASSERT_EQ(3138, node1->index);
	ASSERT_EQ(3138, node2->index);
}

TEST(HashTreeTest, ShouldFindIfKeyIsGreaterThanTableSize)
{
	HashTree hashTree;

	Node* node1 = hashTree.GetNode(255, 65535);

	ASSERT_FALSE(node1->IsEmpty());
	ASSERT_EQ(65311, node1->index);
}

TEST(HashTreeTest, ShouldFindIfCollisionHappened)
{
	HashTree hashTree;

	Node* node1 = hashTree.GetNode(4, 2048);
	Node* node2 = hashTree.GetNode(4);

	ASSERT_FALSE(node1 == node2);
	ASSERT_FALSE(node1->IsEmpty());
	ASSERT_EQ(4, node1->index);
	ASSERT_EQ(2048, node1->parent);
	ASSERT_EQ(4, node1->symbol);

	ASSERT_FALSE(node2->IsEmpty());
	ASSERT_EQ(4, node2->index);
	ASSERT_EQ(-1, node2->parent);
	ASSERT_EQ(4, node2->symbol);
}

TEST(HashTreeTest, ShouldFindString)
{
	HashTree hashTree;

	hashTree.GetNode(99, 56);
	hashTree.GetNode(103,99);
	hashTree.GetNode(103,103);
	Node* node = hashTree.GetNode(107,103);

	ASSERT_FALSE(node->IsEmpty());
	ASSERT_EQ(103, node->parent);
	ASSERT_EQ(107, node->symbol);
}

TEST(HashTreeTest, ShouldNotFindIfTableIsFull)
{
	HashTree hashTree;
	Node* node;
	for(int i = 0; i < 65536; i++)
	{
		node = hashTree.GetNode(99, i);
	}

	ASSERT_TRUE(node == NULL);
}

TEST(HashTreeTest, ShouldFindAllIfTableIsMoreThenCodes)
{
	HashTree hashTree;
	Node* node;
	for(int i = 0; i < 32768; i++)
	{
		node = hashTree.GetNode(99, i);
		ASSERT_TRUE(node != NULL);
	}
}