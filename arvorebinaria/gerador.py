import exrex


def file_name_generator():
    """Generator to generate file names."""
    return exrex.getone(r'[a-zA-Z]{1,50}\.(c|txt|doc|jpg)') 

def file_mode_generator():
    """Generator to generate file modes."""
    return exrex.getone(r'r(o|w)')

def file_weight_generator():
    """Generator to generate file weights."""
    return exrex.getone(r'[1-9]{3,6}')


def file_writer(j):
    """Write the file names and modes to a file."""
    with open('input.txt', 'a') as f:
        f.write(str(j)+'\n')
        for i in range(j):
            f.write(file_name_generator() + " " + file_mode_generator() + " " + file_weight_generator() +"\n")

file_writer(60000)