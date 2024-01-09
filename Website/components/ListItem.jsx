import React, { useEffect, useState } from 'react';
import { API_BASE_URL } from '../src/config';
import '../css/listItemStyles.css';
import axios from 'axios';
import io from 'socket.io-client';


function ListItem() {
  const [palletJacks, setPalletJacks] = useState([]);

  useEffect(() => {
    const socket = io(API_BASE_URL);

    socket.on('palletJacks', (data) => {
      setPalletJacks(data);
    });

    return () => {
      socket.disconnect();
    };
  }, []);
  return (
    <div className="listContainer">
      <ul className="scrollableList">
        {Array.isArray(palletJacks)
          ? palletJacks.map((jack) => (
              <li key={jack.id}>
                <div className="jack-item">
                  <p>Pallet ID: {jack.palletId}</p>
                  <p>Status: {jack.status}</p>
                  <p>Location: {jack.location}</p>
                  <p>Assigned Worker: {jack.assignedWorker}</p>
                  <p>Battery Level: {jack.batteryLevel}</p>
                  <p>Current Weight: {jack.currentWeight}</p>
                </div>
              </li>
            ))
          : <p>Error loading pallet jacks data</p>
        }
      </ul>
    </div>
  );
}

export default ListItem;


// useEffect(() => {
//   axios.get(API_BASE_URL+'/palletJacksData' )
//     .then(response => {
//       setPalletJacks(response.data);
//     })
//     .catch(error => {
//       console.error('There was an error fetching Pallet Jacks data!', error);
//     });
// }, []);