import React, { Component } from 'react';
import './App.css';

const baseUrl = "http://localhost:8012";

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

const humanStep = (i, j, app) => {
    console.log(i, j);
    const board = app.state.board;
    const url = baseUrl + '/nextboard/' + i + '/' + j + '/black';
    fetch(url, {
	method: 'GET',
	headers: new Headers({
	    'Accept': 'application/json'
	})
    }).then((res) => {
	return res.text();
    }).then((res) => {
	const nextResult = JSON.parse(res);
	if (!nextResult.valid) {
	    throw 'invalid move';
	}
	const nextboard = nextResult.board;
	app.setState({
	    board: nextboard
	});
	return fetch(baseUrl + '/ainext', {
	    method: 'GET',
	    headers: new Headers({
		'Accept': 'application/json'
	    })
	});
    }).then((res) => {
    });
}

const makeBlock = (i, j, color, app) => {
    return (
	<div key={i + "-" + j} style={{height: "100px", width: "100px", border: "1px rgb(200, 200, 200) solid", backgroundColor: "#fff170"}} onClick={() => humanStep(i, j, app)}>
	    <div style={{height: "100px", width: "100px", borderRadius: "50px", backgroundColor: color}} />
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
		const color = (data === 1 ? "black" : (data === 0 ? "#fff170" : "white"));
		row.push(makeBlock(i, j, color, this));
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
