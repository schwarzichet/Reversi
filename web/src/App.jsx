import React, { Component } from 'react';
// import logo from './logo.svg';
import './App.css';

const makeInitBoard = () => {
    const retval = [];
    for (let i = 0; i < 8; ++i) {
	const item = [];
	for (let j = 0; j < 8; ++j) {
	    item.push(0);
	}
	retval.push(item);
    }
    retval[3][3] = 1;
    retval[3][4] = -1;
    retval[4][3] = -1;
    retval[4][4] = 1;
    return retval;
}

class App extends Component {
    constructor(props) {
	super(props);
	this.state = {
	    board: makeInitBoard()
	}
    }
    
    render() {
	return (
	    <div className="App">
		<header className="App-header">
		    <h1 className="App-title">Reversi</h1>
		</header>
		<div style={{margin: "auto", width: "800px", height: "800px", backgroundColor: "aqua"}}>
		    {
			//const board = this.state.board;
			//for (let i = 0; i < 8; ++i) {
			//    for (let j = 0; j < 8; ++j) {
			//	const data = board[i][j];
			//    }
			//}
			<div/>
		    }
		</div>
	    </div>
	);
    }
}

export default App;
