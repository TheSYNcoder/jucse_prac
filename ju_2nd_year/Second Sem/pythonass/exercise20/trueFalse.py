from shortAnswer import ShortAnswer


class TrueFalse(ShortAnswer):

    def __init__(self, q, a) -> None:
        super(TrueFalse, self).__init__(q, a)

    def ask_question(self):
        return self.get_text() + '\nIs This statement True or False?'
    
    def get_answer(self):
        return str(self.answer)
    
    def check_answer(self ,ans):
        return str(ans) == str(self.answer)


if __name__ == "__main__":
    q = TrueFalse('Fall 2014 was short', True)
    assert q.get_text() == 'Fall 2014 was short'
    assert q.get_answer() == 'True'
    assert q.ask_question() == 'Fall 2014 was short\nIs This statement True or False?'
    assert not (q.check_answer('ans'))
    assert q.check_answer(True)
    print('All TrueFalse tests passed!')
