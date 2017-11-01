
int NBins(float start, float end, float Binning){
  float distance = end - start;
  float NBins = distance/Binning;
  return int(NBins);
}
