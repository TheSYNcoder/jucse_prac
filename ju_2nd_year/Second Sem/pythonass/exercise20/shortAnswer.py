'''
Models a short answer problem
Created Fall 2014

@author: smn4
'''
from problem import Problem


class ShortAnswer(Problem):
    ''' Model a short-answer question '''
    
    def __init__(self, q, a):
        super(ShortAnswer ,self ).__init__(q)
        ''' Construct a short-answer question with question and answer texts '''
        self.answer = a
              
    def ask_question(self):
        ''' Return the question text '''
        return self.get_text() + '?'
    
    def check_answer(self, a):
        ''' Return True if a is the correct answer; False otherwise '''
        return self.answer == a
    
    def get_answer(self):
        ''' Return the answer text '''
        return self.answer
    
if __name__ == "__main__":
    q = ShortAnswer('question', 'answer')
    assert q.get_text() == 'question'
    assert q.get_answer() == 'answer'
    assert q.ask_question() == 'question?'
    assert not (q.check_answer('ans'))
    assert q.check_answer('answer')
    print('All ShortAnswer tests passed!')