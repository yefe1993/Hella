#include <gtest/gtest.h>
#include "listctr.h"

/*
 * [测试前置思考]
 * 1.待测功能 reverseList算法函数
 * 2.触发方式 listCtr.reverse()
 * 3.初始状态 formatList(m_head)
 * 3.测试独立性 new ListCtr对象
 * 4.测试原子性 const formatList(m_head) -> 只读不写，满足原子性要求，测试稳定
 *
 * ----------------------------------------------------
 *  【测试用例：ReverseListWithFourNodes】 要包含具体的数据值和断言方式
 *
 *  [准备（Arrange）]
 *  1.创建一个 ListCtr 对象（其构造函数内部生成链表 1->2->3->4->NULL）
 *  2.调用该对象的 [m_originalDisplay]，将返回值存入 QString initial
 *  3.使用 EXPECT_EQ(initial, "1->2->3->4->NULL") 断言初始状态正确
 *
 *  [执行（Act）] -> 原子性
 *  4.调用 listCtr.reverse()
 *
 *  [断言（Assert）] -> 原子性
 *  5.再次调用 [m_reversedDisplay]，将返回值存入 QString reversed
 *  6.使用 EXPECT_EQ(reversed, "4->3->2->1->NULL") 断言反转成功
 * ----------------------------------------------------
 *
 */

TEST(ListCtrTest, Positive) {
    QString initial,reversed;
    ListCtr list;
    initial = list.originalDisplay();
    EXPECT_EQ(initial, "1->2->3->4->NULL");

    list.reverse();
    reversed = list.reversedDisplay();
    EXPECT_EQ(reversed, "4->3->2->1->NULL");
}



