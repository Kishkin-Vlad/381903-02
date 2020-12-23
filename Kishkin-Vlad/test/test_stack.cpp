#include<gtest.h>

#include "Collection.h"


TEST(Stack, can_create_stack_with_positive_number_of_elements)
{
    ASSERT_NO_THROW(Stack<int> s(10));
}

TEST(Stack, cant_create_stack_with_negative_number_of_elements)
{
    ASSERT_ANY_THROW(Stack<int> s(-10));
}

TEST(Stack, is_empty)
{
    Stack<int> s(10);

    EXPECT_EQ(true, s.isEmpty());
}

TEST(Stack, is_Full)
{
    Stack<int> s(10);
    for (int i = 0; i < s.getSize(); i++)
    {
        s.add(10);
    }

    EXPECT_EQ(true, s.isFull());
}

TEST(Stack, can_create_copied_stack)
{
    Stack<int> s1(10);

    ASSERT_NO_THROW(Stack<int> s2(s1));
}

TEST(Stack, copied_stack_is_equal_to_source_one)
{
    Stack<int> s1(10);
    s1.add(10);
    s1.add(20);
    s1.add(30);

    Stack<int> s2(s1);

    EXPECT_EQ(true, s1 == s2);
}

TEST(Stack, can_assign_stacks_of_equal_size)
{
    Stack<int> s1(5);
    Stack<int> s2(5);

    ASSERT_NO_THROW(s1 = s2);
}

TEST(Stack, can_assign_stacks_of_different_size)
{
    Stack<int> s1(10);
    Stack<int> s2(5);

    ASSERT_NO_THROW(s1 = s2);
}

TEST(Stack, can_assign_stack_to_itself)
{
    Stack<int> s(5);

    ASSERT_NO_THROW(s = s);
}

TEST(Stack, assign_operator_change_stack_size)
{
    Stack<int> s1(10);
    Stack<int> s2(5);
    s2 = s1;
    EXPECT_EQ(10, s2.getSize());
}

TEST(Stack, compare_equal_stacks)
{
    Stack<int> s1(10);
    s1.add(10);
    s1.add(20);
    s1.add(30);
    Stack<int> s2(s1);

    EXPECT_EQ(true, s1 == s2);
}

TEST(Stack, compare_not_equal_stacks)
{
    Stack<int> s1(10);
    s1.add(10);
    s1.add(20);
    s1.add(30);
    Stack<int> s2(10);
    s2.add(40);
    s2.add(50);

    EXPECT_EQ(false, s1 == s2);
}

TEST(Stack, stacks_with_different_size_are_not_equal)
{
    Stack<int> s1(5), s2(10);

    EXPECT_EQ(false, s1 == s2);
}

TEST(Stack, can_add_element_to_not_full_stack)
{
    Stack<int> s(5);

    ASSERT_NO_THROW(s.add(3));
}

TEST(Stack, cant_add_element_to_full_stack)
{
    Stack<int> s(5);
    for (int i = 0; i < 5; i++)
    {
        s.add(10);
    }

    ASSERT_ANY_THROW(s.add(10));
}

TEST(Stack, can_pop_element_from_not_empty_stack)
{
    Stack<int> s(5);
    s.add(10);

    ASSERT_NO_THROW(s.pop());
}

TEST(Stack, cant_pop_element_from_empty_stack)
{
    Stack<int> s(10);

    ASSERT_ANY_THROW(s.pop());
}

TEST(Stack, can_print_stack)
{
    Stack<int> s;
    s.add(10);
    s.add(20);
    s.add(30);
    s.add(40);

    ASSERT_NO_THROW(s.print());
    cout << endl;
}