class Node
{
    int         action;
    int         visits;  		// # time this node has been visit
    float       reward;  		// reward value
    Node        parent;  		// null if root
    List<Node>  children;
    void update(float value);   // update node and backpropagate to parent
    void addChild(Node child); 	// add child node
}



class Domain     // typically a game
{
   State state;  // current state
   List<Integer> legalActions();    // list of available actions
   int    applyAction(int action);  // returns winner: None/White/Black/Draw
   int    playout();                // returns: win=+1/draw=0/loss=-1
}

// • MCTS and UCT
// • MCTS is the general class of algorithms 
// • UCT is a specific embodiment of MCTS (具體化的方式)
// • UCT = Upper Confidence Bounds for Trees（帶入 Exploit & Explore function）
// • UCT = MCTS + UCB (Upper Confidence Bounds)

void __UCT__Search(State s) {

	// create root Node v_0 with State s_0

	while( /* 在計算預算範圍內 Computational Budget */ ) {
		Node v_child = treePolicy(v_current);
		float reward = defaultPolicy( State(v_child) );
		backUp(v_current, v_child, reward);
	}
	return movement(bestChild(v_current, 0));
}


Node treePolicy(Node v) {

	while( /* v is nonterminal */) {
		if(/* v is not fully expand */) {
			return expand(v);    // Random choose 1.
		} else {
			v = bestChild(v, c); // c 是一個平衡係數, 每一個 node 應該都有一個變動的係數
		}
	}

	return v;
}

void defaultPolicy(State s) {
	while( /* State s is non-terminal */ ) {
		/* choose shape in random from movementList(s) */
		s = doSimulationAction(s, place);
	}
	return /* reward from State s (1 -> win or 0 -> gg) */
}

// 如：Einstein's death means a great loss to science.（愛因斯坦的死對科學是重大的損失） 
// 而Lose是動詞，其意是：失去 
// 如：You will lose all your money, if you indulge yourself in gambling. 
// 而Lost可以是lose的過去式或過去分詞，但它也是一個形容詞，其意是：遺失的，迷途的，如： 
// The lost ring was found yesterday. （昨天找到了那遺失的戒指） 
// The lost child is crying. (那迷途的小孩正在大哭） 

void backUp(Node current, Node v, float r) {
	while( v != current) {
		v.visit = v.visit + 1;
		v.reward = v.reward + r

		/* [IF] efficient backUp for 2-player game, zero-sum game. */
		/* vvvvv add the following code vvvvv */
		/* r = -r */
		
		v = v.parent;
	}
}

Node expand(Node v) {

	return v_child;
}

Node bestChild(Node v, float c) {
	/* get the best one <- all the child from Node v */

	Node bestOne;
	bestOne.reward = v.List[0].reward;

	for( /* iterator though the List */ ){
		 /* check the best child by UCT (很多不同種表示法耶)*/
		 /* UCT = Upper Confidence Bounds for Trees（帶入 Exploit & Explore function）*/
		 /* (Exploit part) node.reward + (Explore part) sqrt( log(node.visit)/ node.parent.visit) */
	}
	return bestOne;
}
