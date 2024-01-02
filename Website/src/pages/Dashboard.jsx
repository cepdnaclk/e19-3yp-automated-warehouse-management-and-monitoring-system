import logo from '/img/PALLETPRO.png';
import { Flex } from '@chakra-ui/react';
import { Grid, GridItem, Text, Image, Stack } from '@chakra-ui/react';
import { Button, ButtonGroup } from '@chakra-ui/react';
import { color } from 'framer-motion';
import { FaSignInAlt, FaUserPlus } from 'react-icons/fa';


export default function Dashboard() {
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
        <a href="#about-us" style={{ color: 'white', textDecoration: 'none', fontSize: '1.5rem', marginLeft: '20px' }}>ABOUT US</a>
        <a href="#contact" style={{ color: 'white', textDecoration: 'none', fontSize: '1.5rem', marginLeft: '20px' }}>CONTACT</a>
        <a href="#services" style={{ color: 'white', textDecoration: 'none', fontSize: '1.5rem', marginLeft: '20px' }}>SERVICES</a>
      </GridItem>
      <GridItem bg='#140d07' area={'nav'} display="flex" flexDirection="column" justifyContent="center" alignItems="center">
        <Flex direction="column" justifyContent="center" alignItems="center" alignSelf="center" mb={4}>
        <Text fontSize="xl" mb='auto' color="white" textAlign='center'>
        <h1 style={{ fontSize: '5rem', marginBottom: '20px' }}>
    WELCOME TO <span style={{ color: 'white' }}>PALLET</span><span style={{ color: '#68EDFF' }}>PRO</span>
  </h1>
</Text>

          <Stack direction='row' spacing={4}>
          <button
  style={{
    color: '#68EDFF',
    backgroundColor: 'transparent',
    border: '2px solid #68EDFF',
    borderRadius: '10px',
    padding: '15px 20px',
    fontSize: '2rem',
    cursor: 'pointer',
  }}
  onMouseEnter={(e) => e.target.style.color = 'white'}
  onMouseLeave={(e) => e.target.style.color = '#68EDFF'}
>
  <FaUserPlus style={{ marginRight: '5px' }} />
  Sign-Up
</button>

<button
  style={{
    color: '#68EDFF',
    backgroundColor: 'transparent',
    border: '2px solid #68EDFF',
    borderRadius: '10px',
    padding: '15px 20px',
    fontSize: '2rem',
    cursor: 'pointer',
    transition: '0.3s'
  }}
  onMouseEnter={(e) => e.target.style.color = 'white'}
  onMouseLeave={(e) => e.target.style.color = '#68EDFF'}
>
  <FaSignInAlt style={{ marginRight: '5px' }} />
  Login
</button>

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
