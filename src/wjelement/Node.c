#include <stdlib.h>
#include <stdio.h>

#include "Node.h"

static void addChildToParent(Node * child, Node * parent){

	NodeListElem * elem = calloc(1,sizeof(NodeListElem));
	elem->child = child;
	elem->next = 0;

	if (!parent->firstChild){
		parent->firstChild = elem;
	}

	NodeListElem * previousLastChild = 0;
	if (parent->lastChild){
		previousLastChild = parent->lastChild;
	}
	if (previousLastChild){
		previousLastChild->next = elem;
	}

	parent->lastChild = elem;
}

Node * NDE_createErrorNode (Node * parent){
	Node * ret = calloc(1,sizeof(Node));

	if (parent){
		addChildToParent(ret, parent);
	}

	return ret;
}

void NDE_clearNode(Node * node){
	if (!node->firstChild){
		free(node->errorMessage);
		free(node);
		return;
	}

	NodeListElem * currentListElem = node->firstChild;
	NodeListElem * nextListElem;

	while (currentListElem){
		nextListElem = currentListElem->next;
		NDE_clearNode(currentListElem->child);
		free(currentListElem);
		currentListElem = nextListElem;
	}

	free(node->errorMessage);
	free(node);
}

void NDE_clearChildren(Node * node){
	if (!node->firstChild){
		return;
	}

	NodeListElem * currentListElem = node->firstChild;
	NodeListElem * nextListElem;

	while (currentListElem){
		nextListElem = currentListElem->next;
		NDE_clearNode(currentListElem->child);
		free(currentListElem);
		currentListElem = nextListElem;
	}

	node->firstChild = NULL;
	node->lastChild = NULL;
}

void NDE_setErrorMessage(Node * node, char * message){
	if (node->errorMessage){
		free(node->errorMessage);
	}
	node->errorMessage = message;
}

static void printTabs(unsigned int tabs){
	unsigned int i;
	for ( i = 0; i < tabs; i++){
		printf("\t");
	}
}

static void dumpNode(Node * node, unsigned int tabs){
	if (node->errorMessage){
		printTabs(tabs);

		printf("%s",node->errorMessage);
		tabs++;
	}

	NodeListElem * currentListElem = node->firstChild;
	NodeListElem * nextListElem;

	while (currentListElem){
		nextListElem = currentListElem->next;
		dumpNode(currentListElem->child, tabs);
		currentListElem = nextListElem;
	}
}

void NDE_dump(Node * node){
	dumpNode(node, 0);
}

