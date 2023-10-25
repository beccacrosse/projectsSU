import { Button, StyleSheet, SafeAreaView, Text, Pressable } from "react-native";
import { useSpotifyAuth , useSpotifyTracks} from "./utils";
import { Themes } from "./assets/Themes";
import * as Images from "./assets/Images";

export default function App() {
  const { token, getSpotifyAuth } = useSpotifyAuth();
  const tracks = useSpotifyTracks(token);

  return (
    <SafeAreaView style={styles.container}>
      {/* TODO: This button is just for testing your auth implementation.
       * Replace this with a Pressable when you can. */}
      <Button title="Test auth" onPress={() => getSpotifyAuth()} />
      <Pressable style={{}} onPress={()=> getSpotifyAuth()}>
       <Image source={Images.images.spotify}/> 
       <Text style={{color: "white"}}>Connect to Spotify</Text>
      </Pressable>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    backgroundColor: Themes.colors.background,
    justifyContent: "center",
    alignItems: "center",
    flex: 1,
  },
  connectBtn : {
    height: 15,
    borderRadius: 8,
    alignItems: "center",
    justifyContent: "center",
    backgroundColor: Themes.colors.spotify,
  }
});
