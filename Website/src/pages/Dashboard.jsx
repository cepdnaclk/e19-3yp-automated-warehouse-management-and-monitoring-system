import logo from '/img/PALLETPRO.png';
import { Flex } from '@chakra-ui/react';
import { Grid, GridItem, Text, Image, Stack} from '@chakra-ui/react'
import { Button, ButtonGroup } from '@chakra-ui/react'
import { EmailIcon } from '@chakra-ui/icons';
import { FaSignInAlt } from 'react-icons/fa';



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
      <GridItem  bg='#140d07' area={'header'}>
        Header
      </GridItem>
      <GridItem  bg='#140d07' area={'nav'}>
        <Text fontSize="xl">Nav</Text>
        <Stack direction='row' spacing={4}>
        <Button colorScheme="teal" mr="4">
          Button 1
        </Button>
        
        <Button leftIcon={<FaSignInAlt />} colorScheme='teal' variant='outline' p={6} fontSize="lg" _hover={{ bg: "teal.500", borderColor: "teal.500" }} _active={{ bg: "teal.700", borderColor: "teal.700" }} _focus={{ boxShadow: "outline" }}>
          Login
        </Button>
        </Stack>

      </GridItem>
      <GridItem  bg='#140d07' area={'main'}>
      <Flex justifyContent="center" alignItems="center" height="100%">
      <Image src={logo} alt="Pallet Pro" boxSize="400px" />
      </Flex>
      </GridItem>
    </Grid>
  )
}