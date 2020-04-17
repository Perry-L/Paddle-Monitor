void Timer(){
  // Timer Alarm Code
  if (ptime >= 0){
    if (timer == HIGH and (ptime <= millis() - timer_time * 1000) and (ptime >= millis() - timer_time * 1000 - 400)) { // check if timer is on and the beem should sound
      tone(BUZZER, 1000); // Send 1KHz sound signal...
    } else if (timer == HIGH and (ptime <= millis() - timer_time * 1000 - 400)) { // check if sound should end... only runs if it should't start
      noTone(BUZZER); //Stop sound...
      ptime = millis(); // reset ptime to repeat
    }
  }
  if (PlayTone){
    tone(BUZZER, 1000, 300);
    PlayTone = LOW;
  }
}
