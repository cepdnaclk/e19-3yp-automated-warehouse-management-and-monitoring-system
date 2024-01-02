import logo from '/img/PALLETPRO.png';
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
      gridTemplateRows={'50px 1fr 30px'}
      gridTemplateColumns={'1fr 1fr'}
      h='100vh'
      color='blackAlpha.700'
      fontWeight='bold'
    >
      <GridItem bg='#140d07' area={'header'} display="flex" justifyContent="flex-end" alignItems="center">
        <a href="#about-us" style={{ color: 'white', textDecoration: 'none', fontSize: '1rem', marginLeft: '30px', transition: 'color 0.3s' }}
          onMouseEnter={(e) => e.target.style.color = '#68EDFF'}
          onMouseLeave={(e) => e.target.style.color = 'white'}
        >
          About Us
        </a>
        <a href="#contact" style={{ color: 'white', textDecoration: 'none', fontSize: '1rem', marginLeft: '30px', transition: 'color 0.3s' }}
          onMouseEnter={(e) => e.target.style.color = '#68EDFF'}
          onMouseLeave={(e) => e.target.style.color = 'white'}
        >
          Contact
        </a>
        <a href="#services" style={{ color: 'white', textDecoration: 'none', fontSize: '1rem', marginLeft: '30px', transition: 'color 0.3s', marginRight:'100px' }}
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
    display: 'flex', // Add this line to make the button a flex container
    alignItems: 'center', // Add this line to vertically align the icon and text
    color: '#68EDFF',
    backgroundColor: 'transparent',
    border: '2px solid #68EDFF',
    borderRadius: '20px',
    padding: '5px 20px', // Decrease padding for smaller button
    fontSize: '1.5rem', // Decrease font size for smaller text
    cursor: 'pointer',
  }}
  onClick={() => setIsSignUpModalOpen(true)}
  onMouseEnter={(e) => e.target.style.color = 'white'}
  onMouseLeave={(e) => e.target.style.color = '#68EDFF'}
>
  <FaUserPlus style={{ marginRight: '5px' }} />
  Sign-Up
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
            Sign-Up
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
            <Button
              colorScheme="teal"
              size="lg"
              onClick={() => {
                
                setIsSignUpModalOpen(false);
              }}
            >
              Sign-Up
            </Button>
          </ModalBody>
        </ModalContent>
      </Modal>

<button
  style={{
    display: 'flex', // Add this line to make the button a flex container
    alignItems: 'center', // Add this line to vertically align the icon and text
    color: '#68EDFF',
    backgroundColor: 'transparent',
    border: '2px solid #68EDFF',
    borderRadius: '20px',
    padding: '5px 20px', // Decrease padding for smaller button
    fontSize: '1.5rem', // Decrease font size for smaller text
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
      <Button
        colorScheme="teal"
        size="lg"
        onClick={() => {
         
          setIsLoginModalOpen(false);
        }}
      >
        Login
      </Button>
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
