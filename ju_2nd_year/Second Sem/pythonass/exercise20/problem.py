'''
Models a problem base class to be inherited
'''

class Problem:

    def __init__(self ,text) -> None:
        self.text = text

    def get_text(self):
        '''
            returns the problem text
        '''
        return self.text
    

