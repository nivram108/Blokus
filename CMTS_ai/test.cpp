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
   State state;  // current state 棋盤的現在狀況
   List<Integer> legalActions();    // list of available actions
                                    // 因為會動態增減 -> 可能不要存成list.
   int    applyAction(int action);  // returns winner: None/White/Black/Draw 模擬棋局->傳回結果
   int    playout();                // returns: win=+1/draw=0/loss=-1
                                    // game.cpp ..... 都在這裡
}

// • MCTS and UCT
// • MCTS is the general class of algorithms
// • UCT is a specific embodiment of MCTS (具體化的方式)
// • UCT = Upper Confidence Bounds for Trees（帶入 Exploit & Explore function）
// • UCT = MCTS + UCB (Upper Confidence Bounds)

// 樹的搜尋:
void __UCT__Search(State s) {

	// create root Node v_0 with State s_0

	while( /* 在計算預算範圍內 Computational Budget */ ) {
		Node v_child = treePolicy(v_current);
		float reward = defaultPolicy( State(v_child) );
		backUp(v_current, v_child, reward);
	}
	return movement(bestChild(v_current, 0));
}

// 根據目前節點 -> 如果還沒達到足夠 child node 就繼續 create node，如果達到個數，開始找最好 node
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

// 如果 State 未結束 (棋盤還能下)，開始做模擬棋局的動作，回傳勝利或是輸惹
void defaultPolicy(State s) {
	while( /* State s is non-terminal */ ) {
		/* choose shape in random from movementList(s) */
		s = doSimulationAction(s, place);
	}
	return /* reward from State s (1 -> win or 0 -> gg) */
}

// 傳回最佳點的權重，一路 backup 更新，一條龍更新上去。
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

// 這我不會說耶，從 Actionlist 選出一個新的 action 嗎？
Node expand(Node v) {

	return v_child;
}

// 從此 node 的 child 選出最棒的那個。
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
