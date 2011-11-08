void RBTransplant(T,u,v) {
	if(u->_parent = _nil)				//1 if( u == root)
		_root = v;						//2 set root to v
	else if(u == u->_parent->_lchild)	//3 if(u is left child)
		u->_parent->_lchild = v;		//4 set left child of u's parent to v
	else u->_parent->_rchild = v;		//5 u must be rchild so set v as rchild
	v->_parent = u->_parent;			//6 reset parent pointer
}

RBNode* RBDelete(T,z) {
	y = z;								//1 temp pointer set to "trouble node"
	Color yOrigColor = y->GetColor();	//2 preserve y orig color
	if(z->_left == _nil){				//3 if lchild is nil
		x = z->_rchild;					//4 set x to z's rchild
		RBTransplant(T,z,z->_rchild);}	//5 swap z & z->rchild
	else if(z->_rchild == _nil){		//6 if rchild of z is nil
		x = z->_lchild;					//7 x is lchild of z
		RBTransplant(T,z,z->_lchild);}	//8 swap z & z->_lchild
	else {								//	z MUST have 2 children
		y = TreeMin(z->_rchild);		//9 set y to z.successor();
		yOrigColor = y->GetColor();		//10 preserve y orig color
		x = y->_rchild;					//11 set x to right child 
		if(y->_parent == z)				//12 successor is also child
			x->_parent = y;				//13 set parent of x to y
		else{							//	successor must not be z's child
			RBTransplant(T,z,z->_rchild);	//14 swap z & z->_rchild
			y->_rchild = z->_rchild;	//15 set right child of y
			y->_rchild->_parent = y;	//16 set parent pointer
		RBTransplant(T,z,y);			//17 swap z & y
		y->_lchild = z->_lchild;		//18 set left child pointer
		y->_lchild->_parent = y;		//19 set parent pointer
		y->SetColor(z->GetColor());		//20 copy color from z
	if(yOrigColor == BLACK)
		RBDeleteFixup(T,x);				//22 run fixup if y was black
}


RBNode* GetUncle(RBNode* node){
	if(node->_parent == node->parent->_parent->_lchild)
		return node->_parent->_parent->_rchild;
	//else
	return node->_parent->_parent->_lchild;
};

