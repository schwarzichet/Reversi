import React, { Component } from 'react';
import './App.css';

const baseUrl = "http://localhost:8012";

let mode = 'human-ai';

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

const aiFirst = () => {
    makeInitBoard();
    fetch(baseUrl + '/start/ai/human');
    mode = 'human-ai';
}

const humanFirst = () => {
    makeInitBoard();
    fetch(baseUrl + '/start/human/ai');
    mode = 'human-ai';
}

const humanToHuman = () => {
    makeInitBoard();
    fetch(baseUrl + '/start/human/human');
    mode = 'human-human';
}

const aiToAi = () => {
    makeInitBoard();
    fetch(baseUrl + '/start/ai/ai');
    mode = 'ai-ai';
}

const humanStep = (i, j, app) => {
    // Now only for Human first.
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
	    alert('invalid move!');
	    throw {reason: 'invalid move'};
	}
	const nextboard = nextResult.board;
	app.setState({
	    board: nextboard
	});
	if (mode !== 'human-ai') {
	    return;
	}
	return fetch(baseUrl + '/ainext', {
	    method: 'GET',
	    headers: new Headers({
		'Accept': 'application/json'
	    })
	});
    }).then((res) => {
	return res.text();
    }).then((res) => {
	const result = JSON.parse(res);
	const {board, column, row, color} = result;
	app.setState({board: board});
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
		    <div style={{height: '100px', margin: 'auto', display: 'flex', flexDirection: 'row'}}>
			<div style={{backgroundColor: 'gray', height: '100px', width: '100px', marginRight: '10px'}}>
			    <span style={{margin: 'auto', fontSize: '20px'}}>AI First</span>
			</div>
			<div style={{backgroundColor: 'gray', height: '100px', width: '100px', marginRight: '10px'}} onClick={humanFirst}>
			    <span style={{margin: 'auto', fontSize: '20px'}}>Human First</span>
			</div>
			<div style={{backgroundColor: 'gray', height: '100px', width: '100px', marginRight: '10px'}}>
			    <span style={{margin: 'auto', fontSize: '20px'}}>Human to human</span>
			</div>
			<div style={{backgroundColor: 'gray', height: '100px', width: '100px', marginRight: '10px'}}>
			    <span style={{margin: 'auto', fontSize: '20px'}}>AI to AI</span>
			</div>
		    </div>
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
