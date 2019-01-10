# Display Youtube Subscriber on 8 Digits LED Display using NodeMCU

Display your Youtube subscriber on 8 Digits LED Display Max7219 using NodeMCU and Arduino IDE.

## Hardware

1. NodeMCU v3        
https://sea.banggood.com/custlink/vvKmdyopw4

2. 8 Digits 7 Segment Max7219    
https://sea.banggood.com/custlink/33KKyRaC1P  


![Menampilkan subscriber Youtube pada LED Display dengan NodeMCU Arduino](https://raw.githubusercontent.com/komputronika/YoutubeSubscriberNodeMCU/master/.github/Menampilkan%20subscriber%20youtube%20pada%20LED%20display%20dengan%20NodeMCU%20Arduino.png)

## Google API Key

You need Google API Key to read subscription data from Youtube. 
Here's a 'simple' way to get the YouTube subscriber number from Google's Youtube API v3:

1. Go to https://console.developers.google.com/apis/library
2. Log in with your Google account.
3. Next to the logo click on 'Project' and 'Create project'. Name it whatever you want and click on 'Create'.
4. Wait until the project is created, the page will switch to it by itself, it will take a couple of seconds up to a minute. Once it's done it will be selected next to the logo.
5. Once it's created and selected, click on 'Credentials' from the menu on the left.
6. Click on 'Create Credentials' and choose 'API Key'. You can restrict it to specific IPs, or types of requests (website, android, ios etc.) if you want, it's safer that way.
7. Copy your API KEY, you will need this in the sketch.

8. Edit file *`Subscriber.ino`*, replace `API_KEY` with you API Key you got in step-7, then replace `CHANNEL_ID` with your channel's ID (it's the code at the end of your channel's URL).

## Wiring

![Wiring](https://raw.githubusercontent.com/komputronika/YoutubeSubscriberNodeMCU/master/.github/g964.png)
