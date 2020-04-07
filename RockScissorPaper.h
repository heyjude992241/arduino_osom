class RockScissorPaper{
  public:
    const static uint8_t MAX_RSP = 3;
    RockScissorPaper(){}
    RockScissorPaper(uint16_t x, uint16_t y, uint8_t order){
      _coor_x = x;
      _coor_y = y;
      _order = order;
    }

    uint8_t getOrder(){
      return _order;
    }

    uint16_t getX(){
      return _coor_x;
    }

    uint16_t getY(){
      return _coor_y;
    }

    uint8_t getBattleResult(int opponent){
      if(_order == 0 && opponent == 0)return 2;
      else if(_order == 0 && opponent == 1) return 1;
      else if(_order == 0 && opponent == 2) return 0;
      else if(_order == 1 && opponent == 0) return 0;
      else if(_order == 1 && opponent == 1) return 2;
      else if(_order == 1 && opponent == 2) return 1;
      else if(_order == 2 && opponent == 0) return 1;
      else if(_order == 2 && opponent == 1) return 0;
      else if(_order == 2 && opponent == 2) return 2;
    }

  private:
    uint8_t _order;
    uint16_t _coor_x, _coor_y;
};
