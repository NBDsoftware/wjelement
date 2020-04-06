#ifndef NODE_H
#define NODE_H

typedef struct _elem {
	struct _node * child;
	struct _elem * next;
} NodeListElem;

typedef struct _node {
	char * errorMessage;
	NodeListElem * firstChild;
	NodeListElem * lastChild;
} Node;

Node * NDE_createErrorNode (Node * parent);
void NDE_clearNode(Node * node);
void NDE_clearChildren(Node * node);
void NDE_setErrorMessage(Node * node, char * message);
void NDE_dump(Node * node);

#endif
