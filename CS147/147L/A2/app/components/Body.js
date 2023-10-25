import { View, StyleSheet, Text, Image, ImageBackground, Pressable, Dimensions } from "react-native";
import * as Device from 'expo-device';
import Profiles from "../../assets/Profiles";
import Emojis from "../../assets/Icons";
import { useState } from "react";
import { Themes } from "../../assets/Themes";


const windowWidth = Dimensions.get("window").width;
const windowHeight = Dimensions.get("window").height;

const Body = () => {
  /* deviceType wasnt working (it kept returning undefined so I tried calculating diagnol length on my own
  //const diagonalSize = Math.sqrt(windowWidth ** 2 + windowHeight ** 2);
  //const isTablet = 18 >= diagonalSize >= 6.5;
  /* the above code didnt work for my google tablet so I used the below code to 
  differentiate between my iphone and my simulatorand it worked.. i understand
   there may be a better way but im too new to this and cant get help atm*/
  const isTablet = (windowWidth > 500)
  console.log(isTablet)
  {isTablet ? [styles.player, styles.playerTablet]
    : styles.player}
  const [isHearted, pressHeart] = useState(false);
 console.log("deviceType is ");
 console.log(Device.deviceType);
  return (
    <View style={styles.container}>
      <View style={isTablet ? styles.mainImageTablet
    : styles.mainImage}>
        <ImageBackground
          source={Profiles.landay.image}
          style={styles.image}
          imageStyle={styles.imageStyle}
        >
        <View style={styles.textContainer}>
          <View>
            <Text style={isTablet ? [styles.name, styles.nameTablet]
    : styles.name}>{Profiles.landay.name}</Text>
          </View>
        </View>
        <View style={styles.bottom}>
          <Text style={isTablet ? [styles.bottomText, {fontSize: 38}]
    : styles.bottomText}>{Profiles.landay.caption}</Text>
          <View style={{}}>
             <Pressable  onPress={ () => pressHeart( !isHearted )} style={styles.pressable}>
              
              {isHearted ? ( <Image source={Emojis.likeOn.light} style={styles.heart}/>)
              : (<Image source={Emojis.likeOff.light} style={styles.heart}/>)}
            </Pressable> 
          </View>
        </View>
        </ImageBackground>
      </View>
      <View style={isTablet ? [styles.voiceBox, styles.voiceBoxTablet]
    : styles.voiceBox}>
        <Text style={isTablet ? [styles.audioText, styles.audioTextTablet]
    : styles.audioText}>My Hottest Take</Text>
        <View style={styles.voiceMemo}>
        <Image source={Emojis.player.light} style={isTablet ? [styles.player, styles.playerTablet]
    : styles.player}/>
        <Image source={Emojis.audioWave.light} style={styles.voice}/>
        </View>
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  container : {
    flexDirection: "column",
    alignItems: "center",
    width: "100%",
    backgroundColor: Themes.light.bg

  },
  image: {
    width: "100%",
    aspectRatio: 1,
    borderRadius: windowWidth / 48.75
  },
  imageTablet :{
    // tablet 
    width: windowHeight * .5,
    aspectRatio: 1,
    borderRadius: windowWidth / 48.75
  },
  imageStyle: {
    borderRadius: windowWidth / 48.75
  },
  mainImageTablet: {
    backgroundColor: Themes.light.bg,
    borderRadius: windowWidth / 48.75,
    width: windowHeight * .5,
    shadowColor: Themes.light.shadows.shadowColor,
    shadowRadius: Themes.light.shadows.shadowRadius,
    shadowOffset: Themes.light.shadows.shadowOffset,
    shadowOpacity: Themes.light.shadows.shadowOpacity,
    
  },
  mainImage: {
    backgroundColor: Themes.light.bg,
    borderRadius: 8,
    shadowColor: Themes.light.shadows.shadowColor,
    shadowRadius: Themes.light.shadows.shadowRadius,
    shadowOffset: Themes.light.shadows.shadowOffset,
    shadowOpacity: Themes.light.shadows.shadowOpacity,
    elevation: 3,

  },
  pressable:{
    height: (windowWidth / 11.14),
    aspectRatio: 1,
    backgroundColor: Themes.light.bgSecondary,
    borderRadius: (windowWidth / 9.75),
    alignItems: "center",
    justifyContent: "center"
  },
  heart : {
    height: (windowWidth / 15.6),
    aspectRatio: 1
  },
  textContainer :{
    flex: 1,
    flexDirection: "column",
    alignContent: "space-between" //idk how this works
  },
  name: {
    fontFamily: "Sydney-Bold",
    color: Themes.light.textSecondary,
    fontSize: (windowWidth / 10.83),
    padding: (windowWidth / 39)
  },
  nameTablet: {
    fontSize: 40
  },
  bottom : {
    padding: (windowWidth / 39),
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center"
  },
  bottomText : {
    fontFamily: "Sydney-Bold",
    color: Themes.light.textSecondary,
    fontSize: (windowWidth /21),
  },
  voiceBox : {
    marginVertical:  windowWidth /10,
    width: "100%",
    padding: windowWidth *.03,
    borderRadius: (windowWidth /19.5),
    backgroundColor: Themes.light.bgSecondary,
    shadowColor: Themes.light.shadows.shadowColor,
    shadowRadius: Themes.light.shadows.shadowRadius,
    shadowOffset: Themes.light.shadows.shadowOffset,
    shadowOpacity: Themes.light.shadows.shadowOpacity,
    elevation: 3,
  },
  voiceBoxTablet: {
    //tablet
    width: windowHeight * .5,
    marginTop:  windowWidth * .01,
    marginBottom: windowWidth * .07,
    height: windowHeight * .17
  },
  audioText :{
    fontFamily: "Sydney-Bold",
    fontSize: (windowWidth / 15.6),
    color: Themes.light.text,
    marginBottom: (windowWidth /19.5)
  },
  audioTextTablet :{
    fontSize: (windowWidth / 18),
    marginBottom: (windowWidth /60)
  },
  voiceMemo :{
    flexDirection: "row",
    alignItems: "center",
    marginBottom: (windowWidth /19.5)
  },
  player : {
    height: (windowWidth / 7.8),
    width: (windowWidth / 7.8),
    marginRight: (windowWidth /25),
  },
  playerTablet : {
    height: (windowWidth / 10),
    width: (windowWidth / 10),
    marginRight: windowWidth *.01,
  },
  voice : {
    width: "78%",
    height: (windowWidth / 10),
  }

});

export default Body;
