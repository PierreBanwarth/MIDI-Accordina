import './App.css';
import React from 'react';
import Select from 'react-select';

const options = [
  { value: 0, label: 'C' },
  { value: 1, label: 'C#' },
  { value: 2, label: 'D' },
  { value: 3, label: 'D#' },
  { value: 4, label: 'E' },
  { value: 5, label: 'F' },
  { value: 6, label: 'F#' },
  { value: 7, label: 'G' },
  { value: 8, label: 'G#' },
  { value: 9, label: 'A' },
  { value: 10, label: 'A#' },
  { value: 11, label: 'B' },
]
const keyboardKeys = [
  [{ push: 1, pull: 1 }, { push: 2, pull: 2 }, { push: 3, pull: 3 }],
  [{ push: 4, pull: 4 }, { push: 5, pull: 5 }, { push: 6, pull: 6 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 1, pull: 1 }],
  [{ push: 1, pull: 1 }, { push: 1, pull: 1 }, { push: 11, pull: 1 }],
];

class Touche extends React.Component {
  constructor(props) {
    super(props);
   
    this.state = {
      push: props.push,
      pull: props.pull
    };
  }
  handleChangePush(result) {
    this.setState({ push: result['value'] });
  }
  handleChangePull(result) {
    this.setState({ pull: result['value'] });
  }

  render() {
    return <td>
      <Select options={options} defaultValue={options[this.state.pull]} onChange={this.handleChangePull.bind(this)} />
      <Select options={options} defaultValue={options[this.state.push]} onChange={this.handleChangePush.bind(this)} />
    </td>; 
  }
}


function Keyboard(props) {
  const listItems = keyboardKeys.map((keyboard, index) =>
    <tr key = { index }>
      <Touche push={keyboard[0].push} pull={keyboard[0].pull}></Touche>
      <Touche push={keyboard[1].push} pull={keyboard[1].pull}></Touche>
      <Touche push={keyboard[2].push} pull={keyboard[2].pull}></Touche>
    </tr>
  );
  return (
    listItems
  );
}

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <table>
          <tbody>
            <Keyboard keyboardKeys={keyboardKeys} />
          </tbody>
        </table>
      </header>
    </div>
  );
}
export default App;
