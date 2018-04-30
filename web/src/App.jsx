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

const humanStep = (i, j) => {
    // TODO:
    return null;
}

const makeBlock = (key, color) => {
    return (
	<div key={key} style={{height: "100px", width: "100px", backgroundColor: color}}>
	    <div/>
	</div>
    );
}

class App extends Component {
    constructor(props) {
	super(props);
	this.state = {
	    board: makeInitBoard()
	}
    }

    renderBoard() {
	const board = this.state.board;
	const retval = [];
	for (let i = 0; i < 8; ++i) {
	    const row = [];
	    for (let j = 0; j < 8; ++j) {
		const data = board[i][j];
		const color = (data === 1 ? "black" : (data === 0 ? "aqua" : "white"));
		row.push(makeBlock(i + "-" + j, color));
	    }
	    retval.push(<div key={i}>{row}</div>);
	}
	return retval;
    }
    
    render() {
	return (
	    <div className="App">
		<header className="App-header">
		    <h1 className="App-title">Reversi</h1>
		</header>
		<div style={{margin: "auto", width: "800px", height: "800px", backgroundColor: "#fff170", display: "flex", flexDirection: "row"}}>
		    {
			this.renderBoard()
		    }
		</div>
	    </div>
	);
    }
}

export default App;
