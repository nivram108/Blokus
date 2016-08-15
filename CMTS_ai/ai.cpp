// AI algorithm will be using to obtain information from Board,
// to know where the game is going and what is allowed to do.

class MonteCarlo(){
    void __init__(self, board, **kwargs){
        // Takes an instance of a Board and optionally some keyword
        // arguments.
        // Initializes the list of game states and the statistics tables.
    }


    void update(self, state){
        // Takes a game state, and appends it to the history.   	
    }


    void get_play(self){
        // Causes the AI to calculate the best move from the
        // current game state and return it. 	
    }


    void run_simulation(self){
        // Plays out a "random" game from the current position,
        // then updates the statistics tables with the result. 	
    }

}
