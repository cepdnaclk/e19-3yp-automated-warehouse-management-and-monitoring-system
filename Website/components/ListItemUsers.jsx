import React from 'react';
import '../css/listItemStyles.css'


function ListItem() {
  const palletJacks = [
    {
      'id': 1,
      'location': 'Base Station',
      'batteryLevel': '100%',
      'weight': '0kg'
    },
    {
      'id': 2,
      'location': 'Storage 3 Block 2',
      'batteryLevel': '90%',
    },
    {
      'id': 3,
      'location': 'Storage 3',
      'batteryLevel': '73%',
      'weight': '74kg'
    },
  ]


  return (
    <div className="listContainer">
      <ul className="scrollableList">
       {palletJacks.map((jack) => (
          <li key={jack.id}>
           <div className="jack-item">
             <p>Pallet ID: {jack.id}</p>
              <p>Location: {jack.location}</p>
              <p>Battery Level: {jack.batteryLevel}</p>
              <p>Current Weight: {jack.weight}</p>
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
}


export default ListItem;
