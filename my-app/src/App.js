import './App.css';
import React from 'react';
import Select from 'react-select';

const options = [
  {value: 0, label: 'C',  color: '##eff8fc'},
  {value: 1, label: 'C#', color: '#ceebf5'},
  {value: 2, label: 'D', color: '#addeef'},
  {value: 3, label: 'D#', color: '#8cd0e9'},
  {value: 4, label: 'E', color: '#6bc3e2'},
  {value: 5, label: 'F', color: '#4ab6dc'},
  {value: 6, label: 'F#', color: '#2aa9d5'},
  {value: 7, label: 'G', color: '#238fb5'},
  {value: 8, label: 'G#', color: '#4#1d7594'},
  {value: 9, label: 'A', color: '#165b73'},
  {value: 10, label: 'A#', color: '#104152'},
  {value: 11, label: 'B', color: '#0a2731'},
]
const styles = {
  option: (provided, state) => ({
    ...provided,
    fontWeight: state.isSelected ? "bold" : "normal",
    color: state.data.color,
    backgroundColor: state.data.bgcolor,
    fontSize: state.selectProps.myFontSize
  }),
  singleValue: (provided, state) => ({
    ...provided,
    color: state.data.color
  })
};

const optionOctave = [
  { value: 0, label: '1' },
  { value: 1, label: '2' },
  { value: 2, label: '3' },
  { value: 3, label: '4' },
]

class Key extends React.Component {
  constructor(props) {
    super(props);
   
    this.state = {
      ligne: props.ligne,
      colonne: props.colonne,
      handleChange: props.onChange,
      dataKey : props.dataKey,
    };
  }

  handleChangeNotePull(event) {
     this.state.handleChange('note','pull', event, this.state)
  }
  handleChangeNotePush(event) {
    this.state.handleChange('note', 'push', event, this.state)
  }
  handleChangeOctavePull(event) {
    this.state.handleChange('octave', 'pull', event, this.state)
  }
  handleChangeOctavePush(event) {
    this.state.handleChange('octave', 'push', event, this.state)
  }

  render() {
    return <td>
      <table>
        <tbody>
          <tr>
            <td>
              <Select className='note-select'  styles={styles} options={options} value={options[this.props.dataKey.pull]} onChange={this.handleChangeNotePull.bind(this)} />
              <Select className='note-select'  styles={styles} options={options} value={options[this.props.dataKey.push]} onChange={this.handleChangeNotePush.bind(this)} />
            </td>
            <td>
              <Select options={optionOctave} value={optionOctave[this.props.dataKey.octpull]} onChange={this.handleChangeOctavePull.bind(this)} />
              <Select options={optionOctave} value={optionOctave[this.props.dataKey.octpush]} onChange={this.handleChangeOctavePush.bind(this)} />
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
    this.state = {
      handleChangeKey: props.onChange,
    }
  }
  handleChange = (type, pushpull, event, buttonState) => {
    this.state.handleChangeKey(type, pushpull ,event, buttonState)
  }
  render() {    
    return (    
      this.props.keyboard.map((row, index) =>
        <tr key={index}>
          {
            row.map(
              (y, ind) =>  <Key key={index+1*ind+1} dataKey={y} onChange={this.handleChange} ligne={index} colonne={ind}></Key>
            )
          }
        </tr>
      )
    )
  }
}
const optionKeyboardDefault = [
  {
    value: 0, 
    label: 'Anglo Concertina'
  },{
    value: 1,
    label: 'Accordéon Chromatique',
  },{
    value: 2,
    label: 'Accordéon Diatonique (Sol/Do)',
  }
]

const instrumentKeyboardData = [
  [
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
  [
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
  ],[
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
]
class KeyboardManager extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      selectedKeyboard: 0,
      currentKeyboard: instrumentKeyboardData[0]
    }
  }

  handleChangeKeyboard(e) {
    var tmp = JSON.parse(JSON.stringify(instrumentKeyboardData[e.value]));
    this.setState({
      selectedKeyboard: e.value,
      currentKeyboard: tmp
    })
  }

  handleChangeKey(type, pushpull, e, buttonState) {
    var tempKeyboard = this.state.currentKeyboard
    if(type === 'note'){
      tempKeyboard[buttonState.ligne][buttonState.colonne][pushpull] = e.value
      this.setState({
        currentKeyboard : tempKeyboard
      })
    }else if(type === 'octave'){
      if(pushpull === 'push'){
        tempKeyboard[buttonState.ligne][buttonState.colonne]['octpush'] = e.value
        this.setState({
          currentKeyboard : tempKeyboard
        })
      }else if(pushpull ==='pull'){
        tempKeyboard[buttonState.ligne][buttonState.colonne]['octpull'] = e.value
        this.setState({
          currentKeyboard : tempKeyboard
        })
      }
    }
  }

  FlattenArray(){
    var result = [
      [],[]
    ]
    var test = [].concat.apply([], this.state.currentKeyboard)
    var push = test.map((
      (row) => row.push + 12*row.octpush)
    )
    result[0] = push
    var pull = test.map((
      (row) => row.pull + 12*row.octpull)
    )
    result[1] = pull
    
    return result;
  }

  render() {
    let value = this.FlattenArray().map(e=>JSON.stringify(e)).join(',\n');

    return (
      <div className='main-content'>
        <Select
          options={optionKeyboardDefault}
          value={optionKeyboardDefault[this.state.selectedKeyboard]}
          onChange={this.handleChangeKeyboard.bind(this)}
        />
        <div className='array-area'>
          <table>
            <tbody>
              <Keyboard keyboard={this.state.currentKeyboard} onChange={this.handleChangeKey.bind(this)}/>
            </tbody>
          </table>
          <div className='result-area'>
            <label>Result</label>
            <textarea readOnly value={value}/>
          </div>
        </div>
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
