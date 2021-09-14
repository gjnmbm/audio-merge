# Merging WAV Audio Files
Merges two WAV files together.

Note: The IDs in the WAV files are arbitrary, 
so they can probably be the same as one of the audio files.
The sizes have to be added together, like chunkSize = chunkSize1 + chunkSize2.

The sound data then has to be combined or appended to each
other.

The entire fmt subchunk, format chunk in riff subchunk, and chunk IDs can remain the same don't need to be changed. 