#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include "../include/lib_func.h"


// ノードを初期化
void initialize_node(node* p, int val)
{
	p->pNext = NULL;
	p->pPrev = NULL;
	p->data = val;
}

// リストを初期化
void initialize_list(list* l)
{
	l->header = NULL;
	l->footer = NULL;
}


// 先頭にデータを追加(双方向リスト)
void push_front(list* l, node* p)
{
	p->pPrev = NULL;
	p->pNext = l->header;//ｐを元先頭につなげるＬ->は構造体のメンバにつなげるもの

	if (l->header != NULL) //もし元のノードが先頭にあったら
	{
		l->header->pPrev = p;
	}
	else {
		l->footer = p;
	}

	l->header = p;
	
}

// 末尾にデータを追加（双方向）
void push_back(list* l, node* p)
{
	p->pNext = NULL;
	p->pPrev = l->footer;//footerはリストの最後の意味

	if (l->footer != NULL)//もし元のノードが最後にあったら
	{
		l->footer->pNext = p;
	}
	else {
		l->header = p;
	}

	l->footer = p;
}

// pのノードを削除（双方向）
void remove_node(list* l, node* p)
{
	if (p == NULL) return;

	// 前のノードのつなぎ替える
	if (p->pPrev != NULL)
		p->pPrev->pNext = p->pNext;

	else
		l->header = p->pNext;  // pが先頭ならheaderをｐの次を先頭にする

	// 次のノードのつなぎ替える
	if (p->pNext != NULL)
		p->pNext->pPrev = p->pPrev;

	else
		l->footer = p->pPrev;  // pが最後ならをｐの前を最後にする

	p->pNext = NULL;//最後にｐにつながっているリンクを切る作業↓も同様
	p->pPrev = NULL;
}

// pの次のノードを削除
void remove_next(list* l, node* p)
{
	if (p == NULL) return;

	node* target = p->pNext;//targetは削除したいノード
	if (target == NULL) return;

	node* next = target->pNext;//ｐ、terget、nextの順にある

	p->pNext = next;//tergetを飛ばしてつなげる

	if (next != NULL)
	{
		next->pPrev = p;
	}
	else
	{
		l->footer = p;
	}

	target->pNext = NULL;//削除したノードをほかにつながらないようにする
	target->pPrev = NULL;
	
}

// pの前のノードを削除
void remove_prev(list* l, node* p)
{
	if (p == NULL || p->pPrev == NULL) return;//ｐのまえが存在しない時

	remove_node(l, p->pPrev);
}


// pの次のノードを取得
node* get_next(list* l, node* p)
{
	if (!p) return NULL;
	return p->pNext;

	return NULL;
}

// pの前のノードを取得
node* get_prev(list* l, node* p)
{
	if (!p) return NULL;
	return p->pPrev;

	return NULL;
}
