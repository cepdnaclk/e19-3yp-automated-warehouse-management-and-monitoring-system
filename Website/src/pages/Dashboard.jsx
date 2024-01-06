import logo from '/img/PALLETPRO1.png';
import { Flex } from '@chakra-ui/react';
import { Grid, GridItem, Text, Image, Stack } from '@chakra-ui/react';
import { Button, ButtonGroup } from '@chakra-ui/react';
import { color } from 'framer-motion';
import { FaSignInAlt, FaUserPlus } from 'react-icons/fa';
import React, { useState } from 'react';
import { Input } from '@chakra-ui/react';
import {
  Modal,
  ModalOverlay,
  ModalContent,
  ModalHeader,
  ModalFooter,
  ModalBody,
  ModalCloseButton,
} from '@chakra-ui/react'
import { Link } from 'react-router-dom';


export default function Dashboard() {
  const [isLoginModalOpen, setIsLoginModalOpen] = useState(false);
  const [isSignUpModalOpen, setIsSignUpModalOpen] = useState(false);
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [name, setName] = useState('');
  const [ssid, setSSID] = useState('');
  const [email, setEmail] = useState('');
  const [phoneNumber, setPhoneNumber] = useState('');
  return (
    <Grid
      templateAreas={`"header header"
                      "nav main"`}
      gridTemplateRows={'50px 1fr'}
      gridTemplateColumns={'1fr 1fr'}
      h='100vh'
      color='blackAlpha.700'
      fontWeight='bold'
    >
      <GridItem bg='#140d07' area={'header'} display="flex" justifyContent="flex-end" alignItems="center">
      <Link to="/admin" style={{ color: 'white', textDecoration: 'none', fontSize: '1rem', marginLeft: '30px', transition: 'color 0.3s' }}
    onMouseEnter={(e) => e.target.style.color = '#68EDFF'}
    onMouseLeave={(e) => e.target.style.color = 'white'}
  >
    About Us
  </Link>
  <Link to="/user" style={{ color: 'white', textDecoration: 'none', fontSize: '1rem', marginLeft: '30px', transition: 'color 0.3s' }}
    onMouseEnter={(e) => e.target.style.color = '#68EDFF'}
    onMouseLeave={(e) => e.target.style.color = 'white'}
  >
    Contact
  </Link>
        <a href="#services" style={{ color: 'white', textDecoration: 'none', fontSize: '1rem', marginLeft: '30px', transition: 'color 0.3s', marginRight:'175px' }}
          onMouseEnter={(e) => e.target.style.color = '#68EDFF'}
          onMouseLeave={(e) => e.target.style.color = 'white'}
        >
          Services
        </a>
      </GridItem>
      <GridItem bg='#140d07' area={'nav'} display="flex" flexDirection="column" justifyContent="center" alignItems="center" height='100%'>
        <Flex direction="column" justifyContent="center" alignItems="center" alignSelf="center" mb={4}>
        <Text fontSize="xl" mb='auto' color="white" textAlign='center'>
        <h1 style={{ fontSize: '5rem', marginBottom: '20px' }}>
    WELCOME TO <span style={{ color: 'white' }}>PALLET</span><span style={{ color: '#68EDFF' }}>PRO</span>
  </h1>
</Text>

          <Stack direction='row' spacing={4}>
          <button
  style={{
    display: 'flex', 
    alignItems: 'center', 
    color: '#68EDFF',
    backgroundColor: 'transparent',
    border: '2px solid #68EDFF',
    borderRadius: '20px',
    padding: '5px 20px', 
    fontSize: '1.5rem', 
    cursor: 'pointer',
  }}
  onClick={() => setIsSignUpModalOpen(true)}
  onMouseEnter={(e) => e.target.style.color = 'white'}
  onMouseLeave={(e) => e.target.style.color = '#68EDFF'}
>
  <FaUserPlus style={{ marginRight: '5px' }} />
  Sign Up
</button>
<Modal isOpen={isSignUpModalOpen} onClose={() => setIsSignUpModalOpen(false)} size="sm" motionPreset="slideInBottom">
        <ModalOverlay />
        <ModalContent
          bg="white"
          color="black"
          borderRadius="8px"
          boxShadow="lg"
          maxW="400px"
          mx="auto"
          my="auto"
        >
          <ModalHeader
            bg="teal.500"
            color="white"
            p={4}
            fontSize="2xl"
            borderTopLeftRadius="8px"
            borderTopRightRadius="8px"
          >
            Sign Up
          </ModalHeader>
          <ModalCloseButton color="black" />
          <ModalBody p={4}>
            <Input
              placeholder="Name"
              value={name}
              onChange={(e) => setName(e.target.value)}
              mb={4}
              variant="filled"
              borderColor="teal.200"
            />
            <Input
              placeholder="SSID"
              value={ssid}
              onChange={(e) => setSSID(e.target.value)}
              mb={4}
              variant="filled"
              borderColor="teal.200"
            />
            <Input
              placeholder="Email"
              value={email}
              onChange={(e) => setEmail(e.target.value)}
              mb={4}
              variant="filled"
              borderColor="teal.200"
            />
            <Input
              placeholder="Phone Number"
              value={phoneNumber}
              onChange={(e) => setPhoneNumber(e.target.value)}
              mb={4}
              variant="filled"
              borderColor="teal.200"
            />
            <Flex justifyContent="center" alignItems="center">
            <Button
              colorScheme="teal"
              size="lg"
              onClick={() => {
                
                setIsSignUpModalOpen(false);
              }}
            >
              Sign Up
            </Button>
            </Flex>
          </ModalBody>
        </ModalContent>
      </Modal>

<button
  style={{
    display: 'flex',
    alignItems: 'center', 
    color: '#68EDFF',
    backgroundColor: 'transparent',
    border: '2px solid #68EDFF',
    borderRadius: '20px',
    padding: '5px 20px', 
    fontSize: '1.5rem', 
    cursor: 'pointer',
    transition: '0.3s'
  }}
  onClick={() => setIsLoginModalOpen(true)}
  onMouseEnter={(e) => e.target.style.color = 'white'}
  onMouseLeave={(e) => e.target.style.color = '#68EDFF'}
>
  <FaSignInAlt style={{ marginRight: '5px' }} />
  Login
</button>
<Modal isOpen={isLoginModalOpen} onClose={() => setIsLoginModalOpen(false)} size="sm" motionPreset="slideInBottom">
  <ModalOverlay />
  <ModalContent
    bg="white"
    color="black"
    borderRadius="8px"
    boxShadow="lg"
    maxW="400px"
    mx="auto"
    my="auto"
  >
    <ModalHeader
      bg="teal.500"
      color="white"
      p={4}
      fontSize="2xl"
      borderTopLeftRadius="8px"
      borderTopRightRadius="8px"
    >
      Login
    </ModalHeader>
    <ModalCloseButton color="black" />
    <ModalBody p={4}>
      <Input
        placeholder="Username"
        value={username}
        onChange={(e) => setUsername(e.target.value)}
        mb={4}
        variant="filled"
        borderColor="teal.200"
      />
      <Input
        type="password"
        placeholder="Password"
        value={password}
        onChange={(e) => setPassword(e.target.value)}
        mb={4}
        variant="filled"
        borderColor="teal.200"
      />
      <Flex justifyContent="center" alignItems="center">
      <Button
        
        colorScheme="teal"
        size="lg"
        onClick={() => {
         
          setIsLoginModalOpen(false);
        }}
      >
        Login
      
      </Button>
      </Flex>
    </ModalBody>
  </ModalContent>
</Modal>



          </Stack>
        </Flex>
      </GridItem>
      <GridItem bg='#140d07' area={'main'}>
        <Flex justifyContent="center" alignItems="center" height="100%">
          <Image src={logo} alt="Pallet Pro" boxSize="400px" />
        </Flex>
      </GridItem>
    </Grid>
    
  )
}
