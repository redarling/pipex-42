# 🔄 pipex

## Project Description

pipex is a project that aims to mimic the behavior of the following shell command:

        < infile cmd1 | cmd2 > outfile

## 🛠️ Installation Instructions

1. Clone the repository using the command:

        git clone https://github.com/redarling/pipex-42.git

2. Navigate to the project directory:

        cd pipex-42

3. Compile the project:

        make

## 💻 Usage

1. Run the program using the command:

        ./pipex file1 cmd1 cmd2 file2

Where `file1` is the input file, `cmd1` and `cmd2` are the commands to be executed, and `file2` is the output file.

For example:

        ./pipex infile.txt cat "sort -n" outfile.txt

## 📝 Author
- [asyvash](https://github.com/redarling)
