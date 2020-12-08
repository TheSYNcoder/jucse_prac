
from shortAnswer import ShortAnswer


class FillInTheBlanks( ShortAnswer):

    def __init__(self ,q ,a ) -> None:
        super( FillInTheBlanks , self ).__init__(q ,a)
    
    def ask_question( self  ):
        return self.get_text() + '\nFill in the blanks'


if __name__ == "__main__":
    q = FillInTheBlanks('Dibble means to ____ like a duck', 'quack')
    assert q.get_text() == 'Dibble means to ____ like a duck'
    assert q.get_answer() == 'quack'
    assert q.ask_question() == 'Dibble means to ____ like a duck\nFill in the blanks'
    assert not (q.check_answer('ans'))
    assert q.check_answer('quack')
    print('All FillintheBlanks tests passed!')
