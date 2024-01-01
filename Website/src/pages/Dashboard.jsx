import logo from '/img/PALLETPRO.png';
import { Flex } from '@chakra-ui/react';
import { Grid, GridItem, Text, Image, Stack } from '@chakra-ui/react';
import { Button } from '@chakra-ui/react';
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
      <GridItem bg='#140d07' area={'header'}>
        Header
      </GridItem>
      <GridItem bg='#140d07' area={'nav'} display="flex" flexDirection="column" justifyContent="center" alignItems="center">
        <Flex direction="column" justifyContent="center" alignItems="center" alignSelf="center" mb={4}>
          <Text fontSize="xl" mb='auto' color="white">Nav</Text>
          <Stack direction='row' spacing={4}>
            <Button
              leftIcon={<FaUserPlus />}
              colorScheme="teal"
              variant='outline'
              p={4}
              fontSize="lg"
              borderRadius="md"
              _hover={{ bg: "teal.500", borderColor: "teal.500", boxShadow: "lg" }}
              _active={{ bg: "teal.700", borderColor: "teal.700", boxShadow: "md" }}
              _focus={{ boxShadow: "outline" }}
            >
              Sign-Up
            </Button>

            <Button
              leftIcon={<FaSignInAlt />}
              colorScheme='teal'
              variant='outline'
              p={4}
              fontSize="lg"
              borderRadius="md"
              _hover={{ bg: "teal.500", borderColor: "teal.500", boxShadow: "lg" }}
              _active={{ bg: "teal.700", borderColor: "teal.700", boxShadow: "md" }}
              _focus={{ boxShadow: "outline" }}
            >
              Login
            </Button>
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
