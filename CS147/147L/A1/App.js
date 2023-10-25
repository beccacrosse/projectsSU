// IMPORTING things we need!
// View, Text, Image, and StyleSheet are core building blocks for React Native apps.
// SafeAreaView is used to ensure the app positions content appropriately around notches and other OS interface elements.
import { Button, View, Text, Image, StyleSheet, SafeAreaView} from 'react-native';
import { useState } from 'react';

// EXPORTING something we build!
// Remember, UI Components are functions under the hood and they return JSX (UI). This App component returns a "SafeAreaView" with more components nested underneath.
export default function App() {
  // Feel free to edit anything inside here!

  const welcomeMessage = "Welcome to my playground!"
  const basePath = './assets/'
  const [logoPath, onClick] = useState(basePath + 'icon.png');

  return (
    <View style={styles.container}>
      <Text style={styles.title}>{welcomeMessage}</Text>
      <Text style={styles.paragraph}>
        Logo path is  
        {logoPath} but I learned from this online source https://stackoverflow.com/questions/41033746/react-native-require-not-working-for-image-source that the source required for images needs to be hardcoded so I can't change the image
      </Text>
      <Button title="Generate Default Icon Path" onPress = { () => onClick(basePath + 'icon.png')}></Button>
      <Button title="Generate Favicon Icon Path" onPress = { () => onClick(basePath + 'favicon.png')}></Button>
      <Button title="Create Snack Icon Image" onPress = { () => <Image style={styles.logo} source={require('./assets/snack-icon.png')} /> }></Button>
        
        <Text>I learned that creating an image inside a button requires a better thought out method because I don't think that image knows where to go evenif its created when clicking the button.. however all possible icons are below for you to see </Text>
      <View style={styles.smallerBox}>
        <Image style={styles.logo} source={require('./assets/icon.png')} />
        <Image style={styles.logo} source={require('./assets/splash.png')} />
        <Image style={styles.logo} source={require('./assets/favicon.png')} />
        <Image style={styles.logo} source={require('./assets/adaptive-icon.png')} />
        <Image style={styles.logo} source={require('./assets/snack-icon.png')} />
        <Text style={{color: '#FFFFFF'}}>Welp thats the end of my playing around I really did learn a lot!</Text>
      </View>
    </View>
  );
  
}

// STYLING for our app!
// Here, we define all the styling that we use in our app. The format is always "const styles = StyleSheet.create({...})". The "styles" object contains style objects. We can access a style X with "styles.X". We will learn more about styles and the "StyleSheet" component next Tuesday:-)
const styles = StyleSheet.create({
  container: {
    flex: 1, // We'll learn about "flex" and other flexbox properties in class!
    flexDirection: 'column', // Try: 'row' or 'column'
    alignItems: 'flex-start', // Try: 'flex-start' or 'center' or 'flex-end' 
    justifyContent: 'center', // Try: 'flex-start' or 'flex-end' or 'space-between' or 'space-around' or 'space evenly'
    backgroundColor: '#CBC3E3', // Try different color hex codes!
    padding: 8, // Try changing this value!
  },
  smallerBox:{
    flex:1,
    flexDirection: 'row',
    flexWrap: 'wrap',
    justifyContent: 'center',
    backgroundColor: '#301934'
  },
  title: {
    fontSize: 60, // Try changing this value!
    fontWeight: 'bold', // Try: 'light' or 'normal' or 'bold'
    textAlign: 'center',
    color: 'pink'
  },
  paragraph: {
    // Try changing these values!
    margin: 24,
    fontSize: 18,
    textAlign: 'center'
  },
  logo: {
    // Try changing these values!
    height: 64,
    width: 64,
    margin: 8,
  }
});
