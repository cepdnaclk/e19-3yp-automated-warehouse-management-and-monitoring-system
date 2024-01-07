import React from 'react';
import '../css/listItemStyles.css'


function ListItem() {
  const palletJacks = [
    {
      'id': 1,
      'status': 'Available',
      'location': 'Base Station',
      'assignedWorker': '',
      'batteryLevel': '100%'
    },
    {
      'id': 2,
      'status': 'Assigned',
      'location': 'Storage 3 Block 2',
      'assignedWorker': 'Dasun',
      'batteryLevel': '90%'
    },
    {
      'id': 3,
      'status': 'Assigned',
      'location': 'Storage 3',
      'assignedWorker': 'Nimnadi',
      'batteryLevel': '73%'
    },
    {
      'id': 4,
      'status': 'Assigned',
      'location': 'Storage 3',
      'assignedWorker': 'Hashini',
      'batteryLevel': '54%'
    },
    {
      'id': 5,
      'status': 'Assigned',
      'location': 'Storage 2 Block 1',
      'assignedWorker': 'Pawani',
      'batteryLevel': '83%'
    },
    {
      'id': 6,
      'status': 'Charging',
      'location': 'Base Station',
      'assignedWorker': '',
      'batteryLevel': '27%'
    },
    {
      'id': 7,
      'status': 'Available',
      'location': 'Base Station',
      'assignedWorker': '',
      'batteryLevel': '100%'
    },
    {
      'id': 8,
      'status': 'Assigned',
      'location': 'Storage 1 Block 16',
      'assignedWorker': 'Dasun',
      'batteryLevel': '58%'
    },
    {
      'id': 9,
      'status': 'Assigned',
      'location': 'Storage 1 Block 8',
      'assignedWorker': '',
      'batteryLevel': '76%'
    },
    {
      'id': 10,
      'status': 'Assigned',
      'location': 'Storage 1',
      'assignedWorker': 'Hasini',
      'batteryLevel': '94%'
    }
  ]


  return (
    <div className="listContainer">
      <ul className="scrollableList">
       {palletJacks.map((jack) => (
          <li key={jack.id}>
            <div className="jack-item">
              <p>Status: {jack.status}</p>
              <p>Location: {jack.location}</p>
              <p>Assigned Worker: {jack.assignedWorker}</p>
              <p>Battery Level: {jack.batteryLevel}</p>
            </div>
          </li>
        ))}
      </ul>
    </div>
  );
}


export default ListItem;
