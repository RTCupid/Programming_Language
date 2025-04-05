# Samurai Programming Language

## Contents
- [0. Introduction](#introduction)
- [1. Frontend](#frontend)
- [2. Backend](#backend)
- [3. Tools](#tools)
- [4. Syntax](#syntax)

## Introduction
I make my programming language. It based on recursive descent and include frontend and backend parts, and run in my processor.

## Frontend
Frontend has Tokenizer (you can see it in file Tokenizer.cpp) that make array of tokens from .txt file, it skip spaces (function SkipSpaces) and check keywords (function IsKeyWord) . Then RecursiveReader (you can see it in file RecursiveReader.cpp) perfoms a recursive descent over the token array and make tree of program. This tree write to file.

## Backend
Backend has reader (file ProgramReader.cpp) that read file from frontend and make tree of program again. Then it make program in my assembly and my processor (https://github.com/RTCupid/Proccessor) do this program.

## Tools
In this project I used graphics methods of debug. For example I used Graphviz to draw trees and check the accuracy of program. You can see example of this tree in Figure 1.

 <img src="/img/TREE.png">
  <div align="center"> Fig. 3.Tree of my program solver square.</div><br>



## Syntax
