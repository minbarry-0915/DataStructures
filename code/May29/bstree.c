#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

bst_t * 
bst_create (size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	bst_t * t = (bst_t *) malloc(sizeof(bst_t)) ;
	t->root = NULL ;
	t->usize = usize ;
	t->cmp = cmp ;
	return t ;
}

//넣을 위치의 부모 시작주소를 리턴
//curr->data는 entry 전체를 가르킴
bst_node_t *
_bst_search (bst_t * t, void * data)
{
	//이전 노드랑 현재노드 저장
	bst_node_t * prev, * curr ;
	prev = NULL ;
	//루트부터 찾을때 까지 돔 
	for (curr = t->root ; curr != NULL && t->cmp(curr->data, data) != 0 ; ) {
		//부모 저장
		prev = curr ;
		if (t->cmp(data, curr->data) < 0) {
			curr = curr->left ;
		}
		else {
			curr = curr->right ;
		}
	} 
	// 현재 노드가 NULL이 아닌 경우 (즉, 데이터를 찾은 경우) 현재 노드를 반환합니다.
	if (curr != NULL)
		return curr ;
	// 못찾으면 이전 노드를 반환합니다.
	return prev ;
}

// 쿼리를 찾아서 해당 쿼리의 데이터를 t에 넣어줌
int
bst_search (bst_t * t, void * data)
{
	bst_node_t * n ; 

	
	n = _bst_search(t, data) ;
	if (n == NULL) //트리에 노드가 없음
		return 0 ;
	if (t->cmp(n->data, data) != 0) //해당 노드를 반환받았지만 일치하지 않을때
		return 0 ;

	memcpy(data, n->data, t->usize) ; //dat 가 key값만 가지고 있음
	return 1 ;
}



int
bst_insert (bst_t * t, void * data) 
{
	//삽입할 위치의 부모를 반환 받음(새로운 데이터 이므로)
	bst_node_t * parent;
	parent = _bst_search(t, data) ;
	if (parent != NULL && t->cmp(parent->data, data) == 0)
		return 0 ;

	//노드 생성
	bst_node_t * n = (bst_node_t *) malloc(sizeof(bst_node_t)) ;
	n->data = (char *) malloc(t->usize) ;
	memcpy(n->data, data, t->usize) ;
	n->left = NULL ;
	n->right = NULL ;
	
	//처음 일때
	if (parent== NULL) {
		t->root = n ;
		n->parent = NULL ;
	}
	//처음이 아닐때 
	else {
		n->parent = parent ;
		//부모보다 작으면 왼쪽
		if (t->cmp(parent->data, n->data) > 0) {
			n->parent->left = n ;
		}
		//부모보다 크면 오른쪽 
		else {
			n->parent->right = n ;
		}
	}
	return 1 ;
}

//앞에서 부터 없앰
int bst_remove(bst_t * t, void * data)
{
    bst_node_t * n;
    // 트리에서 주어진 데이터를 가진 노드를 검색합니다.
    n = _bst_search(t, data);
    // 노드가 없거나, 찾은 노드의 데이터가 주어진 데이터와 일치하지 않는 경우
    if (n == NULL || t->cmp(n->data, data) != 0)
        return 0;  // 제거 실패, 0 반환

    // 왼쪽 자식이 없는 경우
    if (n->left == NULL) {
        // 노드가 루트인 경우
        if (n->parent == NULL) {
            // 오른쪽 자식을 새로운 루트로 설정
            t->root = n->right;
            if (n->right != NULL)
                n->right->parent = NULL;  // 새로운 루트의 부모를 NULL로 설정
        }
        // 노드가 부모의 왼쪽 자식인 경우
        else if (n->parent->left == n) {
            if (n->right != NULL)
                n->right->parent = n->parent;  // 오른쪽 자식의 부모를 현재 노드의 부모로 설정
            n->parent->left = n->right;  // 부모의 왼쪽 자식을 현재 노드의 오른쪽 자식으로 설정
        }
        // 노드가 부모의 오른쪽 자식인 경우
        else /* n->parent->right == n */ {
            if (n->right != NULL)
                n->right->parent = n->parent;  // 오른쪽 자식의 부모를 현재 노드의 부모로 설정
            n->parent->right = n->right;  // 부모의 오른쪽 자식을 현재 노드의 오른쪽 자식으로 설정
        }
        free(n->data);  // 현재 노드의 데이터를 메모리에서 해제
        free(n);  // 현재 노드를 메모리에서 해제
        return 1;  // 제거 성공, 1 반환
    }

    // 왼쪽 자식이 있는 경우 (n->left != NULL)
	// 왼쪽에서 가장 큰값을 현재 노드와 바꿔치기 하는 거임 
	// 현재 노드가 사라지면, 중간값이 왼쪽에서 가장 큰 노드가 되므로,

    bst_node_t * lmax = n->left;
    // 왼쪽 서브트리에서 가장 큰 값을 가진 노드를 찾음 (가장 오른쪽 노드)
    while (lmax->right != NULL) {
        lmax = lmax->right;
    }
    // lmax의 오른쪽 자식이 NULL임 (왼쪽 자식은 있을수도 있음,n보다는 작으면서 가장 큰값)
    lmax->parent->right = lmax->left;  // lmax의 부모의 오른쪽 자식을 lmax의 왼쪽 자식으로 설정
    if (lmax->left != NULL)
        lmax->left->parent = lmax->parent;  // lmax의 왼쪽 자식이 존재하면 부모를 lmax의 부모로 설정
    lmax->left = NULL;

    // lmax의 부모를 현재 노드의 부모로 설정
    lmax->parent = n->parent;
    if (n->parent == NULL) {
        t->root = lmax;  // 현재 노드가 루트인 경우 lmax를 루트로 설정
    }
    else if (n->parent->left == n) {
        n->parent->left = lmax;  // 현재 노드가 부모의 왼쪽 자식인 경우
    }
    else /* (n->parent->right == n) */ {
        n->parent->right = lmax;  // 현재 노드가 부모의 오른쪽 자식인 경우
    }

    // lmax의 자식을 현재 노드의 자식으로 설정
    lmax->left = n->left;
    if (n->left != NULL)
        n->left->parent = lmax;
    lmax->right = n->right;
    if (n->right != NULL)
        n->right->parent = lmax;

    free(n->data);  // 현재 노드의 데이터를 메모리에서 해제
    free(n);  // 현재 노드를 메모리에서 해제

    return 1;  // 제거 성공, 1 반환
}


void
bst_node_print (bst_node_t * n, void (* print)(void * data))
{
	printf("(") ;
	if (n->left != NULL) 
		bst_node_print(n->left, print) ;
	else
		printf("-") ;
	printf(",") ;
	print(n->data) ;
	printf(",") ;
	if (n->right != NULL) 
		bst_node_print(n->right, print) ;
	else
		printf("-") ;
	printf(")") ;
}

void
bst_print (bst_t * t, void (* print)(void * data)) 
{
	if (t->root != NULL)
		bst_node_print(t->root, print) ;
	printf("\n") ;
}

void
bst_node_free (bst_node_t * n)
{
	//왼쪽 죽이고 오른쪽 죽이고 자기 죽이기
	if (n->left != NULL)
		bst_node_free(n->left) ;
	if (n->right != NULL)
		bst_node_free(n->right) ;
	free(n->data) ;
}

void
bst_free (bst_t * t)
{
	if (t->root != NULL) 
		bst_node_free(t->root) ;
	free(t) ;
}
