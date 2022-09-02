#include <iostream>

//Step 1
struct MediaPlayer{
	virtual void play(std::string audioType, std::string fileName) = 0;
	virtual ~MediaPlayer() {};
};

struct AdvancedMediaPlayer {
	virtual void playVlc(std::string fileName) = 0;
	virtual void playMp4(std::string fileName) = 0;
	virtual ~AdvancedMediaPlayer() {};
};

//Step 2
struct VlcPlayer: AdvancedMediaPlayer {

	void playVlc(std::string fileName) {
		std::cout << "Playing vlc file. Name: " << fileName << std::endl;
	}

	void playMp4(std::string fileName) {
		//do nothing
	}
};

struct Mp4Player: public AdvancedMediaPlayer {

	void playVlc(std::string fileName){
		//do nothing
	}

	void playMp4(std::string fileName) {
		std::cout << "Playing mp4 file. Name: " << fileName << std::endl;
	}
};


//Step 3
class MediaAdapter: public MediaPlayer {
	AdvancedMediaPlayer *advancedMusicPlayer;

public:
	MediaAdapter(std::string audioType){
		if(audioType.compare("vlc") == 0){
			advancedMusicPlayer = new VlcPlayer();
		} else if(audioType.compare("mp4") == 0){
			advancedMusicPlayer = new Mp4Player();
		}
	}

	void play(std::string audioType, std::string fileName){
		if(audioType.compare("vlc") == 0){
			advancedMusicPlayer->playVlc(fileName);
		} else if(audioType.compare("mp4") == 0){
			advancedMusicPlayer->playMp4(fileName);
		}
	}
};

//Step 4
struct AudioPlayer: public MediaPlayer {
	void play(std::string audioType, std::string fileName){
		//inbuild suport to play mp4
		if(audioType.compare("mp3") == 0){
			std::cout << "Playing mp3 file. Name: " << fileName << std::endl;
		}
		//mediaPlayer is providing support to play other file formats
		else if(audioType.compare("vlc") == 0 || audioType.compare("mp4") == 0){
			mediaAdapter = new MediaAdapter(audioType);
			mediaAdapter->play(audioType, fileName);
		}
		//any other type...
		else {
			std::cout << "Invalid media. " << audioType << " format not supported." << std::endl;
		}
	}

protected:
		MediaAdapter *mediaAdapter;
};

int main(){
	AudioPlayer audioPlayer;

	audioPlayer.play("mp3", "beyond the horizon.mp3");
	audioPlayer.play("mp4", "alone.mp4");
	audioPlayer.play("vlc", "far far away.vlc");
	audioPlayer.play("avi", "mind me.avi");

	return 0;
}
