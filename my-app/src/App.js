import './App.css';
import React from 'react';
import Select from 'react-select';

const options = [
  {value: 0, label: 'C'},
  {value: 1, label: 'C#'},
  {value: 2, label: 'D'},
  {value: 3, label: 'D#'},
  {value: 4, label: 'E'},
  {value: 5, label: 'F'},
  {value: 6, label: 'F#'},
  {value: 7, label: 'G'},
  {value: 8, label: 'G#'},
  {value: 9, label: 'A'},
  {value: 10, label: 'A#'},
  {value: 11, label: 'B'},
]
const optionOctave = [
  { value: 0, label: '1' },
  { value: 1, label: '2' },
  { value: 2, label: '3' },
  { value: 3, label: '4' },
]

const instrumentKeyboardData = [
  {
    value: 0, 
    label: 'Concertina',
    keyboard : [
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
      [{ push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}, { push: 4, pull: 4 , octpull : 1, octpush : 1}],
    ],
  },
  {
    value: 1,
    label: 'Chroma',
    keyboard: [
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
      [{ push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}, { push: 5, pull: 5 , octpull : 1, octpush : 1}],
    ],
  },
  {
    value: 2,
    label: 'Diato',
    keyboard: [
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
      [{ push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}, { push: 6, pull: 6 , octpull : 1, octpush : 1}],
    ],
  },
  
];
class Touche extends React.Component {
  constructor(props) {
    super(props);
   
    this.state = {
      push: props.dataTouche.push,
      pull: props.dataTouche.pull,
      octpull: props.dataTouche.octpull,
      octpush: props.dataTouche.octpush
    };
  }
  componentWillReceiveProps(nextProps) {
    this.setState({
      push: nextProps.dataTouche.push,
      pull: nextProps.dataTouche.pull,
      octpull: nextProps.dataTouche.octpull,
      octpush: nextProps.dataTouche.octpush
    });
  }
  handleChangePush(result) {
    this.setState({ push: result['value'] });
  }
  handleChangePull(result) {
    this.setState({ pull: result['value'] });
  }
  handleChangePullOctave(result) {
    this.setState({ octpull: result['value'] });
  }
  handleChangePushOctave(result) {
    this.setState({ octpush: result['value'] });
  }
  render() {
    return <td>
      <table>
        <tbody>
          <tr>
            <td>
              <Select options={options} value={options[this.state.pull]} onChange={this.handleChangePull.bind(this)} />
              <Select options={options} value={options[this.state.push]} onChange={this.handleChangePush.bind(this)} />
            </td>
            <td>
              <Select options={optionOctave} value={optionOctave[this.state.octpull]} onChange={this.handleChangePullOctave.bind(this)} />
              <Select options={optionOctave} value={optionOctave[this.state.octpush]} onChange={this.handleChangePushOctave.bind(this)} />
            </td>
          </tr>

       </tbody>
      </table>
    </td>; 
  }
}



class Keyboard extends React.Component {
  constructor(props) {
    super(props);
    this.state = { selectedKeyboard: props.selectedKeyboard}
  }
  componentWillReceiveProps(nextProps) {
    this.setState({ selectedKeyboard: nextProps.selectedKeyboard });
  }
  render() {
    return (    
      this.state.selectedKeyboard.keyboard.map((keyboard, index) =>
        <tr key={index*2}>
          <Touche dataTouche={keyboard[0]} ></Touche>
          <Touche dataTouche={keyboard[1]} ></Touche>
          <Touche dataTouche={keyboard[2]} ></Touche>
        </tr>
      )
    )
  }
}

class KeyboardManager extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      selectedKeyboard: instrumentKeyboardData[0],
    };
  }

  handleChangeKeyboard(result) {
    this.setState({ selectedKeyboard: result });
  }

  render() {
    return (
      <div>
        <Select
          options={instrumentKeyboardData}
          defaultValue={this.state.selectedKeyboard}
          onChange={this.handleChangeKeyboard.bind(this)}
        />
        <table>
          <tbody>
            <Keyboard selectedKeyboard={this.state.selectedKeyboard}/>
          </tbody>
        </table>
      </div>
    );
  }
}

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <KeyboardManager></KeyboardManager>
      </header>
    </div>
  );
}
export default App;
